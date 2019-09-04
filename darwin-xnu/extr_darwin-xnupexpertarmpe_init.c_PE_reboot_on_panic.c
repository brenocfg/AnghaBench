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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int DB_NMI ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PE_i_can_has_debugger (int*) ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
PE_reboot_on_panic(void)
{
	uint32_t debug_flags;

	if (PE_i_can_has_debugger(&debug_flags)
		&& (debug_flags & DB_NMI)) {
		/* kernel debugging is active */
		return FALSE;
	} else {
		return TRUE;
	}
}