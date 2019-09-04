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
struct snprintf_arg {char* str; int remain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int __doprnt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snprintf_arg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf_func ; 

int
vsprintf(char *buf, const char *cfmt, va_list ap)
{
	int retval;
	struct snprintf_arg info;

	info.str = buf;
	info.remain = 999999;

	retval = __doprnt(cfmt, ap, snprintf_func, &info, 10, FALSE);
	if (info.remain >= 1) {
		*info.str++ = '\0';
	}
	return 0;
}