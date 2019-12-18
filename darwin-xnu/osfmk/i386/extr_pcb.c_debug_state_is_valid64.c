#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dr7; scalar_t__ dr0; scalar_t__ dr1; scalar_t__ dr2; scalar_t__ dr3; } ;
typedef  TYPE_1__ x86_debug_state64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_MAX_PAGE_ADDRESS ; 
 int /*<<< orphan*/  dr7d_is_valid (int /*<<< orphan*/ *) ; 

boolean_t
debug_state_is_valid64(x86_debug_state64_t *ds)
{
	if (!dr7d_is_valid((uint32_t *)&ds->dr7))
		return FALSE;

	/*
	 * Don't allow the user to set debug addresses above their max
	 * value
	 */
	if (ds->dr7 & 0x1)
		if (ds->dr0 >= VM_MAX_PAGE_ADDRESS)
			return FALSE;

	if (ds->dr7 & (0x1<<2))
		if (ds->dr1 >= VM_MAX_PAGE_ADDRESS)
			return FALSE;

	if (ds->dr7 & (0x1<<4))
		if (ds->dr2 >= VM_MAX_PAGE_ADDRESS)
			return FALSE;

	if (ds->dr7 & (0x1<<6))
		if (ds->dr3 >= VM_MAX_PAGE_ADDRESS)
			return FALSE;

	/* For x86-64, we must ensure the upper 32-bits of DR7 are clear */
	ds->dr7 &= 0xffffffffULL;

	return TRUE;
}