#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ mode; } ;
struct TYPE_11__ {TYPE_1__ fcr; } ;
struct TYPE_12__ {TYPE_6__* p_lcb; int /*<<< orphan*/  xmit_hold_q; TYPE_2__ peer_cfg; int /*<<< orphan*/  local_cid; int /*<<< orphan*/  remote_cid; scalar_t__ local_id; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_13__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int HCI_DATA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  L2CAP_ADJ_ID ; 
 int /*<<< orphan*/  L2CAP_CMD_DISC_REQ ; 
 int L2CAP_CMD_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_DISC_REQ_LEN ; 
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_adj_id (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2cu_build_header (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  l2cu_set_acl_hci_header (int /*<<< orphan*/ *,TYPE_3__*) ; 

void l2cu_send_peer_disc_req (tL2C_CCB *p_ccb)
{
    BT_HDR  *p_buf, *p_buf2;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_ccb->p_lcb->id++;
    l2cu_adj_id(p_ccb->p_lcb, L2CAP_ADJ_ID);

    p_ccb->local_id = p_ccb->p_lcb->id;

    if ((p_buf = l2cu_build_header(p_ccb->p_lcb, L2CAP_DISC_REQ_LEN, L2CAP_CMD_DISC_REQ, p_ccb->local_id)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no buffer for disc_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, p_ccb->local_cid);

    /* Move all queued data packets to the LCB. In FCR mode, assume the higher
       layer checks that all buffers are sent before disconnecting.
    */
    if (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_BASIC_MODE) {
        while ((p_buf2 = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_hold_q, 0)) != NULL) {
            l2cu_set_acl_hci_header (p_buf2, p_ccb);
            l2c_link_check_send_pkts (p_ccb->p_lcb, p_ccb, p_buf2);
        }
    }

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}