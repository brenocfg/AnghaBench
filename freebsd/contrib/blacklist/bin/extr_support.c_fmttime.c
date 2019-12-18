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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/ * localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char*,struct tm*) ; 

const char *
fmttime(char *b, size_t l, time_t t)
{
	struct tm tm;
	if (localtime_r(&t, &tm) == NULL)
		snprintf(b, l, "*%jd*", (intmax_t)t);
	else
		strftime(b, l, "%Y/%m/%d %H:%M:%S", &tm);
	return b;
}