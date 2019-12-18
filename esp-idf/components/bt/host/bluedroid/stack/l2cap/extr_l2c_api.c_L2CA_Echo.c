#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ link_state; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2CA_ECHO_DATA_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_10__ {int /*<<< orphan*/ * p_echo_data_cb; } ;
struct TYPE_9__ {int offset; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BT_BD_ANY ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_ADJ_BRCM_ID ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 scalar_t__ LST_CONNECTED ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__ l2cb ; 
 int /*<<< orphan*/  l2cu_adj_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_send_peer_echo_req (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

BOOLEAN  L2CA_Echo (BD_ADDR p_bd_addr, BT_HDR *p_data, tL2CA_ECHO_DATA_CB *p_callback)
{
    tL2C_LCB    *p_lcb;
    UINT8       *pp;

    L2CAP_TRACE_API ("L2CA_Echo() BDA: %08X%04X",
                     ((p_bd_addr[0] << 24) + (p_bd_addr[1] << 16) + (p_bd_addr[2] <<  8) + (p_bd_addr[3])),
                     ((p_bd_addr[4] <<  8) + (p_bd_addr[5])));

    /* Fail if we have not established communications with the controller */
    if (!BTM_IsDeviceUp()) {
        return (FALSE);
    }

    if ((memcmp(BT_BD_ANY, p_bd_addr, BD_ADDR_LEN) == 0) && (p_data == NULL)) {
        /* Only register callback without sending message. */
        l2cb.p_echo_data_cb = p_callback;
        return TRUE;
    }

    /* We assume the upper layer will call this function only when the link is established. */
    if ((p_lcb = l2cu_find_lcb_by_bd_addr (p_bd_addr, BT_TRANSPORT_BR_EDR)) == NULL) {
        L2CAP_TRACE_ERROR ("L2CA_Echo ERROR : link not established");
        return FALSE;
    }

    if (p_lcb->link_state != LST_CONNECTED) {
        L2CAP_TRACE_ERROR ("L2CA_Echo ERROR : link is not connected");
        return FALSE;
    }

    /* Save address of callback */
    l2cb.p_echo_data_cb = p_callback;

    /* Set the pointer to the beginning of the data */
    pp = (UINT8 *)(p_data + 1) + p_data->offset;
    l2cu_adj_id(p_lcb, L2CAP_ADJ_BRCM_ID);  /* Make sure not using Broadcom ID */
    l2cu_send_peer_echo_req (p_lcb, pp, p_data->len);

    return (TRUE);

}