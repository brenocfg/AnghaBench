#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rmt_name_timer_ent; int /*<<< orphan*/  remname_bda; int /*<<< orphan*/  remname_active; } ;
typedef  TYPE_1__ tBTM_INQUIRY_VAR_ST ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GAP_BleCancelReadPeerDevName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN btm_ble_cancel_remote_name(BD_ADDR remote_bda)
{
    tBTM_INQUIRY_VAR_ST      *p_inq = &btm_cb.btm_inq_vars;
    BOOLEAN     status = TRUE;

#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE && GATTS_INCLUDED == TRUE)
    status = GAP_BleCancelReadPeerDevName(remote_bda);
#endif

    p_inq->remname_active = FALSE;
    memset(p_inq->remname_bda, 0, BD_ADDR_LEN);
    btu_stop_timer(&p_inq->rmt_name_timer_ent);

    return status;
}