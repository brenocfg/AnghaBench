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
 int /*<<< orphan*/  VM_ENTRY_CONTROLS ; 
 int /*<<< orphan*/  VM_EXIT_CONTROLS ; 
 int /*<<< orphan*/  vmcs_clear_bits (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void clear_atomic_switch_msr_special(unsigned long entry,
		unsigned long exit)
{
	vmcs_clear_bits(VM_ENTRY_CONTROLS, entry);
	vmcs_clear_bits(VM_EXIT_CONTROLS, exit);
}