#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ transport; int handle; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_8__ {int non_flushable_pbf; } ;
struct TYPE_7__ {int offset; scalar_t__ len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 scalar_t__ BT_TRANSPORT_LE ; 
 scalar_t__ HCI_DATA_PREAMBLE_SIZE ; 
 int L2CAP_BLE_SIGNALLING_CID ; 
 int /*<<< orphan*/  L2CAP_CMD_BUF_SIZE ; 
 int L2CAP_CMD_OVERHEAD ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_PKT_START ; 
 int L2CAP_PKT_START_NON_FLUSHABLE ; 
 int L2CAP_PKT_TYPE_SHIFT ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int L2CAP_SIGNALLING_CID ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ l2cb ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

BT_HDR *l2cu_build_header (tL2C_LCB *p_lcb, UINT16 len, UINT8 cmd, UINT8 id)
{
    BT_HDR  *p_buf = (BT_HDR *)osi_malloc(L2CAP_CMD_BUF_SIZE);
    UINT8   *p;

    if (!p_buf) {
        return (NULL);
    }

    p_buf->offset = L2CAP_SEND_CMD_OFFSET;
    p_buf->len = len + HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;
    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET;

    /* Put in HCI header - handle + pkt boundary */
#if (BLE_INCLUDED == TRUE)
    if (p_lcb->transport == BT_TRANSPORT_LE) {
        UINT16_TO_STREAM (p, (p_lcb->handle | (L2CAP_PKT_START_NON_FLUSHABLE << L2CAP_PKT_TYPE_SHIFT)));
    } else
#endif
    {
#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
        UINT16_TO_STREAM (p, p_lcb->handle | l2cb.non_flushable_pbf);
#else
        UINT16_TO_STREAM (p, (p_lcb->handle | (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT)));
#endif
    }

    UINT16_TO_STREAM (p, len + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD);
    UINT16_TO_STREAM (p, len + L2CAP_CMD_OVERHEAD);

#if (BLE_INCLUDED == TRUE)
    if (p_lcb->transport == BT_TRANSPORT_LE) {
        //counter_add("l2cap.ble.tx.bytes", p_buf->len);
        //counter_add("l2cap.ble.tx.pkts", 1);

        UINT16_TO_STREAM (p, L2CAP_BLE_SIGNALLING_CID);
    } else
#endif
    {
        //counter_add("l2cap.sig.tx.bytes", p_buf->len);
        //counter_add("l2cap.sig.tx.pkts", 1);
        UINT16_TO_STREAM (p, L2CAP_SIGNALLING_CID);
    }

    /* Put in L2CAP command header */
    UINT8_TO_STREAM  (p, cmd);
    UINT8_TO_STREAM  (p, id);
    UINT16_TO_STREAM (p, len);

    return (p_buf);
}