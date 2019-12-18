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
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTIF_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  btif_dm_proc_loc_oob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_co_loc_oob(BOOLEAN valid, BT_OCTET16 c, BT_OCTET16 r)
{
#if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE)
    BTIF_TRACE_DEBUG("bta_dm_co_loc_oob, valid = %d", valid);
#ifdef BTIF_DM_OOB_TEST
    btif_dm_proc_loc_oob(valid, c, r);
#endif
#else
    BTIF_TRACE_DEBUG("bta_dm_co_loc_oob: func not ported\n");
#endif /* #if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE) */
}