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
 unsigned long percpu_counter_read_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_committed_as ; 

unsigned long vm_memory_committed(void)
{
	return percpu_counter_read_positive(&vm_committed_as);
}