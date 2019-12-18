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
 int /*<<< orphan*/  ESCAPE_CODE ; 
 int /*<<< orphan*/  KERNEL_ENTER_SWITCH_CODE ; 
 int /*<<< orphan*/  KERNEL_EXIT_SWITCH_CODE ; 
 int /*<<< orphan*/  add_event_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_kernel_ctx_switch(unsigned int in_kernel)
{
	add_event_entry(ESCAPE_CODE);
	if (in_kernel)
		add_event_entry(KERNEL_ENTER_SWITCH_CODE);
	else
		add_event_entry(KERNEL_EXIT_SWITCH_CODE);
}