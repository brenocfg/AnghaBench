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
 scalar_t__ LONG_MIN ; 
 long strtox (char const*,char**,int,scalar_t__) ; 

long strtol(const char *restrict s, char **restrict p, int base)
{
	return strtox(s, p, base, 0UL+LONG_MIN);
}