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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 size_t __strftime_l (char*,size_t,char const*,struct tm const*,int /*<<< orphan*/ ) ; 

size_t strftime(char *restrict s, size_t n, const char *restrict f, const struct tm *restrict tm)
{
	return __strftime_l(s, n, f, tm, CURRENT_LOCALE);
}