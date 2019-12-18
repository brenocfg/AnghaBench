#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u64_t ;
struct net_buf_simple {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {scalar_t__ addr; } ;
struct bt_mesh_net_rx {int /*<<< orphan*/  friend_cred; TYPE_1__ ctx; int /*<<< orphan*/  local_match; } ;
struct TYPE_5__ {scalar_t__ frnd; } ;
struct TYPE_6__ {TYPE_2__ lpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_WARN (char*,...) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_NODE ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int TRANS_CTL_OP (int*) ; 
#define  TRANS_CTL_OP_ACK 137 
#define  TRANS_CTL_OP_FRIEND_CLEAR 136 
#define  TRANS_CTL_OP_FRIEND_CLEAR_CFM 135 
 int TRANS_CTL_OP_FRIEND_OFFER ; 
#define  TRANS_CTL_OP_FRIEND_POLL 134 
#define  TRANS_CTL_OP_FRIEND_REQ 133 
#define  TRANS_CTL_OP_FRIEND_SUB_ADD 132 
#define  TRANS_CTL_OP_FRIEND_SUB_CFM 131 
#define  TRANS_CTL_OP_FRIEND_SUB_REM 130 
#define  TRANS_CTL_OP_FRIEND_UPDATE 129 
#define  TRANS_CTL_OP_HEARTBEAT 128 
 TYPE_3__ bt_mesh ; 
 int bt_mesh_friend_clear (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_friend_clear_cfm (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_friend_poll (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_friend_req (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_friend_sub_add (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_friend_sub_rem (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 int /*<<< orphan*/  bt_mesh_lpn_established () ; 
 int bt_mesh_lpn_friend_clear_cfm (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_lpn_friend_offer (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_lpn_friend_sub_cfm (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int bt_mesh_lpn_friend_update (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int trans_ack (struct bt_mesh_net_rx*,int,struct net_buf_simple*,int /*<<< orphan*/ *) ; 
 int trans_heartbeat (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 

__attribute__((used)) static int ctl_recv(struct bt_mesh_net_rx *rx, u8_t hdr,
                    struct net_buf_simple *buf, u64_t *seq_auth)
{
    u8_t ctl_op = TRANS_CTL_OP(&hdr);

    BT_DBG("OpCode 0x%02x len %u", ctl_op, buf->len);

    switch (ctl_op) {
    case TRANS_CTL_OP_ACK:
        return trans_ack(rx, hdr, buf, seq_auth);
    case TRANS_CTL_OP_HEARTBEAT:
        return trans_heartbeat(rx, buf);
    }

    /* Only acks and heartbeats may need processing without local_match */
    if (!rx->local_match) {
        return 0;
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_NODE) && bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND) && !bt_mesh_lpn_established()) {
            switch (ctl_op) {
            case TRANS_CTL_OP_FRIEND_POLL:
                return bt_mesh_friend_poll(rx, buf);
            case TRANS_CTL_OP_FRIEND_REQ:
                return bt_mesh_friend_req(rx, buf);
            case TRANS_CTL_OP_FRIEND_CLEAR:
                return bt_mesh_friend_clear(rx, buf);
            case TRANS_CTL_OP_FRIEND_CLEAR_CFM:
                return bt_mesh_friend_clear_cfm(rx, buf);
            case TRANS_CTL_OP_FRIEND_SUB_ADD:
                return bt_mesh_friend_sub_add(rx, buf);
            case TRANS_CTL_OP_FRIEND_SUB_REM:
                return bt_mesh_friend_sub_rem(rx, buf);
            }
        }

#if defined(CONFIG_BLE_MESH_LOW_POWER)
        if (ctl_op == TRANS_CTL_OP_FRIEND_OFFER) {
            return bt_mesh_lpn_friend_offer(rx, buf);
        }

        if (rx->ctx.addr == bt_mesh.lpn.frnd) {
            if (ctl_op == TRANS_CTL_OP_FRIEND_CLEAR_CFM) {
                return bt_mesh_lpn_friend_clear_cfm(rx, buf);
            }

            if (!rx->friend_cred) {
                BT_WARN("Message from friend with wrong credentials");
                return -EINVAL;
            }

            switch (ctl_op) {
            case TRANS_CTL_OP_FRIEND_UPDATE:
                return bt_mesh_lpn_friend_update(rx, buf);
            case TRANS_CTL_OP_FRIEND_SUB_CFM:
                return bt_mesh_lpn_friend_sub_cfm(rx, buf);
            }
        }
#endif /* CONFIG_BLE_MESH_LOW_POWER */
    }

    BT_WARN("Unhandled TransOpCode 0x%02x", ctl_op);

    return -ENOENT;
}