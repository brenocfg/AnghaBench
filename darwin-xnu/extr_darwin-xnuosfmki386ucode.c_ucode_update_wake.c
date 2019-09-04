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
 int /*<<< orphan*/  cpu_number () ; 
 scalar_t__ global_update ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_microcode () ; 

void
ucode_update_wake()
{
	if (global_update) {
		kprintf("ucode: Re-applying update after wake (CPU #%d)\n", cpu_number());
		update_microcode();
#if DEBUG
	} else {
		kprintf("ucode: No update to apply (CPU #%d)\n", cpu_number());
#endif
	}
}