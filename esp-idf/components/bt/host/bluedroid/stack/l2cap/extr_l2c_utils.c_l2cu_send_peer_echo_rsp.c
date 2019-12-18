#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ cur_echo_id; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {scalar_t__ (* get_acl_data_size_classic ) () ;scalar_t__ (* get_acl_packet_size_classic ) () ;} ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ BT_HDR_SIZE ; 
 scalar_t__ HCI_DATA_PREAMBLE_SIZE ; 
 scalar_t__ L2CAP_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  L2CAP_CMD_ECHO_RSP ; 
 scalar_t__ L2CAP_CMD_OVERHEAD ; 
 scalar_t__ L2CAP_ECHO_RSP_LEN ; 
 scalar_t__ L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,...) ; 
 TYPE_5__* controller_get_interface () ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2cu_build_header (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 

void l2cu_send_peer_echo_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len)
{
    BT_HDR  *p_buf;
    UINT8   *p;
    UINT16   maxlen;
    /* Filter out duplicate IDs or if available buffers are low (intruder checking) */
    if (!id || id == p_lcb->cur_echo_id) {
        /* Dump this request since it is illegal */
        L2CAP_TRACE_WARNING ("L2CAP ignoring duplicate echo request (%d)", id);
        return;
    } else {
        p_lcb->cur_echo_id = id;
    }

    uint16_t acl_data_size = controller_get_interface()->get_acl_data_size_classic();
    uint16_t acl_packet_size = controller_get_interface()->get_acl_packet_size_classic();
    /* Don't return data if it does not fit in ACL and L2CAP MTU */
    maxlen = (L2CAP_CMD_BUF_SIZE > acl_packet_size) ?
               acl_data_size : (UINT16)L2CAP_CMD_BUF_SIZE;
    maxlen -= (UINT16)(BT_HDR_SIZE + HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD +
                       L2CAP_CMD_OVERHEAD + L2CAP_ECHO_RSP_LEN);

    if (data_len > maxlen) {
        data_len = 0;
    }

    if ((p_buf = l2cu_build_header (p_lcb, (UINT16)(L2CAP_ECHO_RSP_LEN + data_len), L2CAP_CMD_ECHO_RSP, id)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no buffer for echo_rsp");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    if (data_len) {
        ARRAY_TO_STREAM  (p, p_data, data_len);
    }

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}