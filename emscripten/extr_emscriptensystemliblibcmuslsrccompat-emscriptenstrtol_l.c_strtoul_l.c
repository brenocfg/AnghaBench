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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 unsigned long strtoul (char const*,char**,int) ; 

unsigned long strtoul_l(const char *restrict s, char **restrict p, int base, locale_t loc)
{
	return strtoul(s, p, base);
}