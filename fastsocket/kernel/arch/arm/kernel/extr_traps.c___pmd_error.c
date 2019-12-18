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
 int /*<<< orphan*/  printk (char*,char const*,int,unsigned long) ; 

void __pmd_error(const char *file, int line, unsigned long val)
{
	printk("%s:%d: bad pmd %08lx.\n", file, line, val);
}