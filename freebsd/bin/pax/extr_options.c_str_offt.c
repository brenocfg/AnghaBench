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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ LONG_MAX ; 
 scalar_t__ QUAD_MAX ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoq (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
str_offt(char *val)
{
	char *expr;
	off_t num, t;

#	ifdef NET2_STAT
	num = strtol(val, &expr, 0);
	if ((num == LONG_MAX) || (num <= 0) || (expr == val))
#	else
	num = strtoq(val, &expr, 0);
	if ((num == QUAD_MAX) || (num <= 0) || (expr == val))
#	endif
		return(0);

	switch(*expr) {
	case 'b':
		t = num;
		num *= 512;
		if (t > num)
			return(0);
		++expr;
		break;
	case 'k':
		t = num;
		num *= 1024;
		if (t > num)
			return(0);
		++expr;
		break;
	case 'm':
		t = num;
		num *= 1048576;
		if (t > num)
			return(0);
		++expr;
		break;
	case 'w':
		t = num;
		num *= sizeof(int);
		if (t > num)
			return(0);
		++expr;
		break;
	}

	switch(*expr) {
		case '\0':
			break;
		case '*':
		case 'x':
			t = num;
			num *= str_offt(expr + 1);
			if (t > num)
				return(0);
			break;
		default:
			return(0);
	}
	return(num);
}