#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool input(float ** & A, unsigned int & rows, unsigned int & columns) 
{
	char op;
	string c;
	getline(cin, c);
	istringstream d(c);
	if ((d >> rows) && (d >> op) && (op == ',') && (d >> columns)) 
	{
		A = new float *[rows];
		for (unsigned int i = 0; i < rows; ++i) 
		{
			A[i] = new float[columns];
			string str;
			getline(cin, str);
			istringstream stream(str);
			for (unsigned int j = 0; j<columns; ++j) 
			{
				if (!(stream >> A[i][j])) 
					return false;
			}
		}
	}
	else return false;
	return true;
}

bool add(float **lhs_elements, unsigned int lhs_rows, unsigned int lhs_columns, float **rhs_elements, unsigned int rhs_rows, unsigned int rhs_columns, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns) 
{
	if (lhs_rows != rhs_rows || lhs_columns != rhs_columns) 
		return false;
	result_rows = lhs_rows; result_columns = lhs_columns;
	result_elements = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) 
	{
		result_elements[i] = new float[result_columns];
		for (unsigned int j = 0; j<result_columns; ++j) 
		{
			result_elements[i][j] = lhs_elements[i][j] + rhs_elements[i][j];
		}
	}
	return true;
}

bool sub(float **lhs_elements, unsigned int lhs_rows, unsigned int lhs_columns, float **rhs_elements, unsigned int rhs_rows, unsigned int rhs_columns, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns) 
{
	if (lhs_rows != rhs_rows || lhs_columns != rhs_columns) 
		return false;
	result_rows = lhs_rows; result_columns = lhs_columns;
	result_elements = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) 
	{
		result_elements[i] = new float[result_columns];
		for (unsigned int j = 0; j<result_columns; ++j) 
		{
			result_elements[i][j] = lhs_elements[i][j] - rhs_elements[i][j];
		}
	}
	return true;
}

bool multiply(float **lhs_elements, unsigned int lhs_rows, unsigned int lhs_columns, float **rhs_elements, unsigned int rhs_rows, unsigned int rhs_columns, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns) 
{
	if (lhs_columns != rhs_rows) 
		return false;
	result_rows = lhs_rows; result_columns = rhs_columns;
	result_elements = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) 
	{
		result_elements[i] = new float[result_columns];
		for (unsigned int j = 0; j<result_columns; ++j) 
		{
			float result_op = 0;
			for (unsigned int k = 0; k<lhs_columns; ++k) 
			{
				result_op += lhs_elements[i][k] * rhs_elements[k][j];
			}
			result_elements[i][j] = result_op;
		}
	}
	return true;
}

bool transpose(float **A, unsigned int rows, unsigned int columns, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns) 
{
	result_rows = columns; result_columns = rows;
	result_elements = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) 
	{
		result_elements[i] = new float[result_columns];
		for (unsigned int j = 0; j<result_columns; ++j) 
		{
			result_elements[i][j] = A[j][i];
		}
	}
	return true;
}

bool reverse(float **A, unsigned int rows, unsigned int columns, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns, bool & b) 
{
	if (rows != columns)
		return false;
	result_rows = rows; result_columns = columns;
	result_elements = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) 
	{
		result_elements[i] = new float[result_columns];
	}
	float a;
	float **B = new float *[rows];
	for (unsigned int i = 0; i < rows; i++) 
	{
		B[i] = new float[rows];
	}
	for (unsigned int i = 0; i < rows; i++) 
	{
		for (unsigned int j = 0; j < rows; j++) 
		{
			B[i][j] = 0;
			if (i == j)
				B[i][j] = 1;
		}
	}
	for (unsigned int k = 0; k < rows; k++) 
	{
		a = A[k][k];
		if (a == 0) 
		{
			b = 1;
			return true;
		}
		for (unsigned int j = 0; j < rows; j++) 
		{
			A[k][j] /= a;
			B[k][j] /= a;
		}
		for (unsigned int i = k + 1; i < rows; i++) 
		{
			a = A[i][k];
			for (unsigned int j = 0; j < rows; j++) 
			{
				A[i][j] -= A[k][j] * a;
				B[i][j] -= B[k][j] * a;
			}
		}
	}
	for (int k = rows - 1; k > 0; k--) 
	{
		for (int i = k - 1; i >= 0; i--) 
		{
			a = A[i][k];
			for (unsigned int j = 0; j < rows; j++) 
			{
				A[i][j] -= A[k][j] * a;
				B[i][j] -= B[k][j] * a;
			}
		}
	}
	for (unsigned int i = 0; i < rows; i++) 
	{
		for (unsigned int j = 0; j < rows; j++) 
		{
			A[i][j] = B[i][j];
			result_elements[i][j] = A[i][j];
		}
	}
	return true;
}

void destroy(float ** & A, unsigned int & rows) 
{
	for (unsigned int i = 0; i<rows; ++i) 
	{
		delete[]A[i];
	}
	delete[]A;
}

int main() 
{
	float **lhs_elements;
	unsigned int lhs_rows, lhs_columns;
	if (!(input(lhs_elements, lhs_rows, lhs_columns))) 
	{
		cout << "An error has occured while reading input data" << endl;
		return -1;
	}
	char op;
	cin >> op;
	cin.get();
	if ((op != '+') && (op != '-') && (op != '*') && (op != 'R') && (op != 'T')) 
	{
		cout << "An error has occured while reading input data" << endl;
		return -2;
	}
	float **result_elements;
	unsigned int result_rows, result_columns;
	switch (op) 
	{
	case '+': 
	{
		float **rhs_elements;
		unsigned int rhs_rows, rhs_columns;
		if (!(input(rhs_elements, rhs_rows, rhs_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(add(lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case '-': 
	{
		float **rhs_elements;
		unsigned int rhs_rows, rhs_columns;
		if (!(input(rhs_elements, rhs_rows, rhs_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(sub(lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case '*': 
	{
		float **rhs_elements;
		unsigned int rhs_rows, rhs_columns;
		if (!(input(rhs_elements, rhs_rows, rhs_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(multiply(lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case 'T': 
	{
		if (!(transpose(lhs_elements, lhs_rows, lhs_columns, result_elements, result_rows, result_columns))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case 'R': 
	{
		bool b = 0;
		if (!(reverse(lhs_elements, lhs_rows, lhs_columns, result_elements, result_rows, result_columns, b))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		if (b) 
		{
			cout << "There is no reverse matrix" << endl;
			return -20;
		}
		break;
	}
	}
	destroy(lhs_elements, lhs_rows);
	for (unsigned int i = 0; i < result_rows; ++i) 
	{
		for (unsigned int j = 0; j < result_columns; ++j) 
		{
			cout << result_elements[i][j] << " ";
		}
		cout << endl;
	}
	destroy(result_elements, result_rows);
	return 0;
}
