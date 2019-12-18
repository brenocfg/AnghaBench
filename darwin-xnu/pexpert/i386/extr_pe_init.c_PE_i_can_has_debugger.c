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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_ALLOW_KERNEL_DEBUGGER ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ csr_check (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_boot_arg ; 
 int /*<<< orphan*/  debug_boot_arg_inited ; 

uint32_t
PE_i_can_has_debugger(uint32_t *debug_flags)
{
#if DEVELOPMENT || DEBUG
	if (debug_flags) {
		assert(debug_boot_arg_inited);
	}
#endif

#if CONFIG_CSR
	if (csr_check(CSR_ALLOW_KERNEL_DEBUGGER) != 0) {
		if (debug_flags)
			*debug_flags = 0;
		return FALSE;
	}
#endif
	if (debug_flags) {
		*debug_flags = debug_boot_arg;
	}
	return TRUE;
}