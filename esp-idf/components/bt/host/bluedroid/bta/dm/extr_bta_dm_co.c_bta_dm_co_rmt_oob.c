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
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTIF_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_dm_ci_rmt_oob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btif_dm_proc_rmt_oob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_co_rmt_oob(BD_ADDR bd_addr)
{
    BT_OCTET16 p_c;
    BT_OCTET16 p_r;
    BOOLEAN result = FALSE;

#ifdef BTIF_DM_OOB_TEST
#if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE)
    result = btif_dm_proc_rmt_oob(bd_addr, p_c, p_r);
#else
    BTIF_TRACE_DEBUG("bta_dm_rmt_oob: func not ported\n");
#endif /* #if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE) */
#endif

    BTIF_TRACE_DEBUG("bta_dm_co_rmt_oob: result=%d", result);
    bta_dm_ci_rmt_oob(result, bd_addr, p_c, p_r);
}