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
typedef  int /*<<< orphan*/  va_list ;
struct snprintf_arg {char* str; size_t remain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int __doprnt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snprintf_arg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf_func ; 

int
vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	struct snprintf_arg info;
	int retval;

	info.str = str;
	info.remain = size;
	retval = __doprnt(format, ap, snprintf_func, &info, 10, FALSE);
	if (info.remain >= 1)
		*info.str++ = '\0';
	return retval;
}