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
typedef  int /*<<< orphan*/  tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2C_CCB ;
typedef  int /*<<< orphan*/  tL2CAP_CHNL_PRIORITY ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_CONNECTIONLESS_CID ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  l2cu_change_pri_ccb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2cu_find_lcb_by_bd_addr (int*,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_UCDSetTxPriority ( BD_ADDR rem_bda, tL2CAP_CHNL_PRIORITY priority )
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;

    L2CAP_TRACE_API ("L2CA_UCDSetTxPriority()  priority: 0x%02x  BDA: %08x%04x", priority,
                     (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3],
                     (rem_bda[4] << 8) + rem_bda[5]);

    if ((p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda, BT_TRANSPORT_BR_EDR)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no LCB for L2CA_UCDSetTxPriority");
        return (FALSE);
    }

    /* Find the channel control block */
    if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, L2CAP_CONNECTIONLESS_CID)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no CCB for L2CA_UCDSetTxPriority");
        return (FALSE);
    }

    /* it will update the order of CCB in LCB by priority and update round robin service variables */
    l2cu_change_pri_ccb (p_ccb, priority);

    return (TRUE);
}