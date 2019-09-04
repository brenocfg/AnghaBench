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
 scalar_t__ debug_boot_arg ; 
 scalar_t__ debug_enabled ; 

uint32_t
PE_i_can_has_debugger(uint32_t *debug_flags)
{
	if (debug_flags) {
#if DEVELOPMENT || DEBUG
		assert(debug_boot_arg_inited);
#endif
		if (debug_enabled)
			*debug_flags = debug_boot_arg;	
		else
			*debug_flags = 0;
	}
	return (debug_enabled);
}