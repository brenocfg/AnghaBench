#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  att_lcid; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_PSM_ATT ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_CH_CONN ; 
 scalar_t__ GATT_CH_OPEN ; 
 int /*<<< orphan*/  L2CAP_ATT_CID ; 
 int /*<<< orphan*/  L2CA_ConnectFixedChnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_ConnectReq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gatt_get_ch_state (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

BOOLEAN gatt_connect (BD_ADDR rem_bda, tBLE_ADDR_TYPE bd_addr_type, tGATT_TCB *p_tcb, tBT_TRANSPORT transport)
{
    BOOLEAN             gatt_ret = FALSE;

    if (gatt_get_ch_state(p_tcb) != GATT_CH_OPEN) {
        gatt_set_ch_state(p_tcb, GATT_CH_CONN);
    }

    if (transport == BT_TRANSPORT_LE) {
        p_tcb->att_lcid = L2CAP_ATT_CID;
        gatt_ret = L2CA_ConnectFixedChnl (L2CAP_ATT_CID, rem_bda, bd_addr_type);
#if (CLASSIC_BT_GATT_INCLUDED == TRUE)
    } else {
        if ((p_tcb->att_lcid = L2CA_ConnectReq(BT_PSM_ATT, rem_bda)) != 0) {
            gatt_ret = TRUE;
        }
#endif  ///CLASSIC_BT_GATT_INCLUDED == TRUE

    }

    return gatt_ret;
}