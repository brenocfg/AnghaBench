#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* p_first_ccb; } ;
struct TYPE_11__ {TYPE_1__ ccb_queue; } ;
typedef  TYPE_4__ tL2C_LCB ;
struct TYPE_12__ {TYPE_3__* p_rcb; struct TYPE_12__* p_next_ccb; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {scalar_t__ pL2CA_QoSViolationInd_Cb; } ;
struct TYPE_10__ {TYPE_2__ api; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CEVT_LP_QOS_VIOLATION_IND ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* l2cu_find_lcb_by_handle (int /*<<< orphan*/ ) ; 

BOOLEAN l2c_link_hci_qos_violation (UINT16 handle)
{
    tL2C_LCB        *p_lcb;
#if (CLASSIC_BT_INCLUDED == TRUE)
    tL2C_CCB        *p_ccb;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    /* See if we have a link control block for the connection */
    p_lcb = l2cu_find_lcb_by_handle (handle);

    /* If we don't have one, maybe an SCO link. */
    if (!p_lcb) {
        return (FALSE);
    }
#if (CLASSIC_BT_INCLUDED == TRUE)
    /* For all channels, tell the upper layer about it */
    for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb) {
        if (p_ccb->p_rcb->api.pL2CA_QoSViolationInd_Cb) {
            l2c_csm_execute (p_ccb, L2CEVT_LP_QOS_VIOLATION_IND, NULL);
        }
    }
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    return (TRUE);
}