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
typedef  int dtrace_optval_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 size_t strlen (char const*) ; 
 int strtoull (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_optval_parse(const char *arg, dtrace_optval_t *rval)
{
	dtrace_optval_t mul = 1;
	size_t len;
	char *end;

	len = strlen(arg);
	errno = 0;

	switch (arg[len - 1]) {
	case 't':
	case 'T':
		mul *= 1024;
		/*FALLTHRU*/
	case 'g':
	case 'G':
		mul *= 1024;
		/*FALLTHRU*/
	case 'm':
	case 'M':
		mul *= 1024;
		/*FALLTHRU*/
	case 'k':
	case 'K':
		mul *= 1024;
		/*FALLTHRU*/
	default:
		break;
	}

	errno = 0;
	*rval = strtoull(arg, &end, 0) * mul;

	if ((mul > 1 && end != &arg[len - 1]) || (mul == 1 && *end != '\0') ||
	    *rval < 0 || errno != 0)
		return (-1);

	return (0);
}