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
 int /*<<< orphan*/  bfin_remove_all_hw_break () ; 
 scalar_t__ kgdb_single_step ; 

int kgdb_arch_init(void)
{
	kgdb_single_step = 0;

	bfin_remove_all_hw_break();
	return 0;
}