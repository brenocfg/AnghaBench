#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

double _atof( const char **stringPtr ) {
	const char	*string;
	float sign;
	float value;
	int		c = '0'; // bk001211 - uninitialized use possible

	string = *stringPtr;

	// skip whitespace
	while ( *string <= ' ' ) {
		if ( !*string ) {
			*stringPtr = string;
			return 0;
		}
		string++;
	}

	// check sign
	switch ( *string ) {
	case '+':
		string++;
		sign = 1;
		break;
	case '-':
		string++;
		sign = -1;
		break;
	default:
		sign = 1;
		break;
	}

	// read digits
	value = 0;
	if ( string[0] != '.' ) {
		do {
			c = *string++;
			if ( c < '0' || c > '9' ) {
				break;
			}
			c -= '0';
			value = value * 10 + c;
		} while ( 1 );
	}

	// check for decimal point
	if ( c == '.' ) {
		double fraction;

		fraction = 0.1;
		do {
			c = *string++;
			if ( c < '0' || c > '9' ) {
				break;
			}
			c -= '0';
			value += c * fraction;
			fraction *= 0.1;
		} while ( 1 );

	}

	// not handling 10e10 notation...
	*stringPtr = string;

	return value * sign;
}