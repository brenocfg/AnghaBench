#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ att_lcid; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {int offset; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_CONGESTED ; 
 int /*<<< orphan*/  GATT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 scalar_t__ L2CAP_ATT_CID ; 
 scalar_t__ L2CAP_DW_CONGESTED ; 
 scalar_t__ L2CAP_DW_FAILED ; 
 scalar_t__ L2CA_DataWrite (scalar_t__,TYPE_2__*) ; 
 scalar_t__ L2CA_SendFixedChnlData (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 

tGATT_STATUS attp_send_msg_to_l2cap(tGATT_TCB *p_tcb, BT_HDR *p_toL2CAP)
{
    UINT16      l2cap_ret;


    if (p_tcb->att_lcid == L2CAP_ATT_CID) {
        l2cap_ret = L2CA_SendFixedChnlData (L2CAP_ATT_CID, p_tcb->peer_bda, p_toL2CAP);
    } else {
#if (CLASSIC_BT_INCLUDED == TRUE)
        l2cap_ret = (UINT16) L2CA_DataWrite (p_tcb->att_lcid, p_toL2CAP);
#else
        l2cap_ret = L2CAP_DW_FAILED;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    }

    if (l2cap_ret == L2CAP_DW_FAILED) {
        GATT_TRACE_DEBUG("ATT   failed to pass msg:0x%0x to L2CAP",
                         *((UINT8 *)(p_toL2CAP + 1) + p_toL2CAP->offset));
        return GATT_INTERNAL_ERROR;
    } else if (l2cap_ret == L2CAP_DW_CONGESTED) {
        GATT_TRACE_DEBUG("ATT congested, message accepted");
        return GATT_CONGESTED;
    }
    return GATT_SUCCESS;
}