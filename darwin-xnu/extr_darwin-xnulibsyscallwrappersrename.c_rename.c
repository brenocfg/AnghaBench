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
 int /*<<< orphan*/  __inc_remove_counter () ; 
 int __rename (char const*,char const*) ; 

int
rename(const char *old, const char *new)
{
	int res = __rename(old, new);
	if (res == 0) __inc_remove_counter();
	return res;
}