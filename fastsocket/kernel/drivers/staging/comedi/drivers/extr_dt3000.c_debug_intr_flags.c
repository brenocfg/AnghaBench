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
 int /*<<< orphan*/ * intr_flags ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void debug_intr_flags(unsigned int flags)
{
	int i;
	printk("dt3k: intr_flags:");
	for (i = 0; i < 8; i++) {
		if (flags & (1 << i)) {
			printk(" %s", intr_flags[i]);
		}
	}
	printk("\n");
}