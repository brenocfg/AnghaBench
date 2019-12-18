#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_present; } ;
typedef  TYPE_1__ tL2CAP_CFG_INFO ;
struct TYPE_10__ {int /*<<< orphan*/  att_lcid; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_11__ {int /*<<< orphan*/  local_mtu; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  GATT_CH_CFG ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_CONN_NO_RESOURCES ; 
 scalar_t__ L2CAP_CONN_OK ; 
 int /*<<< orphan*/  L2CA_ConfigReq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  L2CA_ConnectRsp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_2__* gatt_allocate_tcb_by_bdaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ gatt_default ; 
 TYPE_2__* gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gatt_l2cif_connect_ind_cback (BD_ADDR  bd_addr, UINT16 lcid, UINT16 psm, UINT8 id)
{
    /* do we already have a control channel for this peer? */
    UINT8       result = L2CAP_CONN_OK;
    tL2CAP_CFG_INFO cfg;
    tGATT_TCB       *p_tcb = gatt_find_tcb_by_addr(bd_addr, BT_TRANSPORT_BR_EDR);
    UNUSED(psm);

    GATT_TRACE_ERROR("Connection indication cid = %d", lcid);
    /* new connection ? */
    if (p_tcb == NULL) {
        /* allocate tcb */
        if ((p_tcb = gatt_allocate_tcb_by_bdaddr(bd_addr, BT_TRANSPORT_BR_EDR)) == NULL) {
            /* no tcb available, reject L2CAP connection */
            result = L2CAP_CONN_NO_RESOURCES;
        } else {
            p_tcb->att_lcid = lcid;
        }

    } else { /* existing connection , reject it */
        result = L2CAP_CONN_NO_RESOURCES;
    }

    /* Send L2CAP connect rsp */
    L2CA_ConnectRsp(bd_addr, id, lcid, result, 0);

    /* if result ok, proceed with connection */
    if (result == L2CAP_CONN_OK) {
        /* transition to configuration state */
        gatt_set_ch_state(p_tcb, GATT_CH_CFG);

        /* Send L2CAP config req */
        memset(&cfg, 0, sizeof(tL2CAP_CFG_INFO));
        cfg.mtu_present = TRUE;
        cfg.mtu = gatt_default.local_mtu;

        L2CA_ConfigReq(lcid, &cfg);
    }

}