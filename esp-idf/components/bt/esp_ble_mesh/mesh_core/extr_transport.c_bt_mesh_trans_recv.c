#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8_t ;
typedef  scalar_t__ u64_t ;
struct net_buf_simple_state {int dummy; } ;
struct net_buf_simple {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_dst; int /*<<< orphan*/  addr; } ;
struct bt_mesh_net_rx {int friend_match; scalar_t__ net_if; int /*<<< orphan*/  local_match; int /*<<< orphan*/  friend_cred; int /*<<< orphan*/  seq; TYPE_2__ ctx; TYPE_1__* sub; } ;
typedef  enum bt_mesh_friend_pdu_type { ____Placeholder_bt_mesh_friend_pdu_type } bt_mesh_friend_pdu_type ;
struct TYPE_3__ {int /*<<< orphan*/  net_idx; } ;

/* Variables and functions */
 int BLE_MESH_FRIEND_PDU_SINGLE ; 
 int /*<<< orphan*/  BLE_MESH_NET_HDR_LEN ; 
 scalar_t__ BLE_MESH_NET_IF_ADV ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  BT_WARN (char*) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_LOW_POWER ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_NODE ; 
 int EAGAIN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ SEG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANS_SEQ_AUTH_NVAL ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_friend_enqueue_rx (struct bt_mesh_net_rx*,int,scalar_t__*,unsigned int,struct net_buf_simple*) ; 
 int bt_mesh_friend_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_lpn_established () ; 
 int /*<<< orphan*/  bt_mesh_lpn_msg_received (struct bt_mesh_net_rx*) ; 
 scalar_t__ bt_mesh_lpn_timer () ; 
 scalar_t__ bt_mesh_lpn_waiting_update () ; 
 int /*<<< orphan*/  net_buf_simple_pull (struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_simple_restore (struct net_buf_simple*,struct net_buf_simple_state*) ; 
 int /*<<< orphan*/  net_buf_simple_save (struct net_buf_simple*,struct net_buf_simple_state*) ; 
 int trans_seg (struct net_buf_simple*,struct bt_mesh_net_rx*,int*,scalar_t__*,unsigned int*) ; 
 int trans_unseg (struct net_buf_simple*,struct bt_mesh_net_rx*,scalar_t__*) ; 

int bt_mesh_trans_recv(struct net_buf_simple *buf, struct bt_mesh_net_rx *rx)
{
    u64_t seq_auth = TRANS_SEQ_AUTH_NVAL;
    enum bt_mesh_friend_pdu_type pdu_type = BLE_MESH_FRIEND_PDU_SINGLE;
    struct net_buf_simple_state state;
    u8_t seg_count = 0U;
    int err;

    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND)) {
        rx->friend_match = bt_mesh_friend_match(rx->sub->net_idx,
                                                rx->ctx.recv_dst);
    } else {
        rx->friend_match = false;
    }

    BT_DBG("src 0x%04x dst 0x%04x seq 0x%08x friend_match %u",
           rx->ctx.addr, rx->ctx.recv_dst, rx->seq, rx->friend_match);

    /* Remove network headers */
    net_buf_simple_pull(buf, BLE_MESH_NET_HDR_LEN);

    BT_DBG("Payload %s", bt_hex(buf->data, buf->len));

    /* If LPN mode is enabled messages are only accepted when we've
     * requested the Friend to send them. The messages must also
     * be encrypted using the Friend Credentials.
     */
    if (IS_ENABLED(CONFIG_BLE_MESH_NODE) && bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_LOW_POWER) &&
                bt_mesh_lpn_established() && rx->net_if == BLE_MESH_NET_IF_ADV &&
                (!bt_mesh_lpn_waiting_update() || !rx->friend_cred)) {
            BT_WARN("Ignoring unexpected message in Low Power mode");
            return -EAGAIN;
        }
    }

    /* Save the app-level state so the buffer can later be placed in
     * the Friend Queue.
     */
    net_buf_simple_save(buf, &state);

    if (SEG(buf->data)) {
        /* Segmented messages must match a local element or an
         * LPN of this Friend.
         */
        if (!rx->local_match && !rx->friend_match) {
            return 0;
        }

        err = trans_seg(buf, rx, &pdu_type, &seq_auth, &seg_count);
    } else {
        seg_count = 1U;
        err = trans_unseg(buf, rx, &seq_auth);
    }

    /* Notify LPN state machine so a Friend Poll will be sent. If the
     * message was a Friend Update it's possible that a Poll was already
     * queued for sending, however that's fine since then the
     * bt_mesh_lpn_waiting_update() function will return false:
     * we still need to go through the actual sending to the bearer and
     * wait for ReceiveDelay before transitioning to WAIT_UPDATE state.
     * Another situation where we want to notify the LPN state machine
     * is if it's configured to use an automatic Friendship establishment
     * timer, in which case we want to reset the timer at this point.
     *
     */
    if (IS_ENABLED(CONFIG_BLE_MESH_NODE) && bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_LOW_POWER) &&
                (bt_mesh_lpn_timer() ||
                 (bt_mesh_lpn_established() && bt_mesh_lpn_waiting_update()))) {
            bt_mesh_lpn_msg_received(rx);
        }
    }

    net_buf_simple_restore(buf, &state);

    if (IS_ENABLED(CONFIG_BLE_MESH_NODE) && bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND) && rx->friend_match && !err) {
            if (seq_auth == TRANS_SEQ_AUTH_NVAL) {
                bt_mesh_friend_enqueue_rx(rx, pdu_type, NULL,
                                          seg_count, buf);
            } else {
                bt_mesh_friend_enqueue_rx(rx, pdu_type, &seq_auth,
                                          seg_count, buf);
            }
        }
    }

    return err;
}