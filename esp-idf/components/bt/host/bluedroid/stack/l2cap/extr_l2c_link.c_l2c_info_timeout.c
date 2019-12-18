#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* p_first_ccb; } ;
struct TYPE_9__ {scalar_t__ link_state; TYPE_1__ ccb_queue; int /*<<< orphan*/  remote_bd_addr; scalar_t__ w4_info_rsp; int /*<<< orphan*/  info_timer_entry; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_10__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ tL2C_CONN_INFO ;
struct TYPE_11__ {scalar_t__ chnl_state; struct TYPE_11__* p_next_ccb; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_INFO ; 
 scalar_t__ CST_ORIG_W4_SEC_COMP ; 
 scalar_t__ CST_TERM_W4_SEC_COMP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_WAIT_INFO_RSP_TOUT ; 
 int /*<<< orphan*/  L2CEVT_L2CAP_INFO_RSP ; 
 scalar_t__ LST_DISCONNECTED ; 
 scalar_t__ LST_DISCONNECTING ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void l2c_info_timeout (tL2C_LCB *p_lcb)
{
    tL2C_CCB   *p_ccb;
#if (CLASSIC_BT_INCLUDED == TRUE)
    tL2C_CONN_INFO  ci;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    /* If we timed out waiting for info response, just continue using basic if allowed */
    if (p_lcb->w4_info_rsp) {
        /* If waiting for security complete, restart the info response timer */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb) {
            if ( (p_ccb->chnl_state == CST_ORIG_W4_SEC_COMP) || (p_ccb->chnl_state == CST_TERM_W4_SEC_COMP) ) {
                btu_start_timer (&p_lcb->info_timer_entry, BTU_TTYPE_L2CAP_INFO, L2CAP_WAIT_INFO_RSP_TOUT);
                return;
            }
        }

        p_lcb->w4_info_rsp = FALSE;
#if (CLASSIC_BT_INCLUDED == TRUE)
        /* If link is in process of being brought up */
        if ((p_lcb->link_state != LST_DISCONNECTED) &&
                (p_lcb->link_state != LST_DISCONNECTING)) {
            /* Notify active channels that peer info is finished */
            if (p_lcb->ccb_queue.p_first_ccb) {
                ci.status = HCI_SUCCESS;
                memcpy (ci.bd_addr, p_lcb->remote_bd_addr, sizeof(BD_ADDR));

                for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb) {
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_INFO_RSP, &ci);
                }
            }
        }
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    }
}