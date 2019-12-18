#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_buf_simple_state {int dummy; } ;
struct net_buf_simple {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_dst; int /*<<< orphan*/  addr; } ;
struct bt_mesh_net_rx {int local_match; size_t msg_cache_idx; int /*<<< orphan*/  friend_match; TYPE_1__ ctx; int /*<<< orphan*/  rssi; } ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  enum bt_mesh_net_if { ____Placeholder_bt_mesh_net_if } bt_mesh_net_if ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_ADDR_IS_UNICAST (int /*<<< orphan*/ ) ; 
 int BLE_MESH_NET_IF_PROXY ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT_WARN (char*) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_GATT_PROXY_SERVER ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_BUF_SIMPLE_DEFINE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bt_mesh_elem_find (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_fixed_group_match (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_net_decode (struct net_buf_simple*,int,struct bt_mesh_net_rx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_mesh_net_relay (int /*<<< orphan*/ *,struct bt_mesh_net_rx*) ; 
 int /*<<< orphan*/  bt_mesh_proxy_addr_add (struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_trans_recv (int /*<<< orphan*/ *,struct bt_mesh_net_rx*) ; 
 int /*<<< orphan*/  buf ; 
 unsigned long long* msg_cache ; 
 size_t msg_cache_next ; 
 int /*<<< orphan*/  net_buf_simple_restore (int /*<<< orphan*/ *,struct net_buf_simple_state*) ; 
 int /*<<< orphan*/  net_buf_simple_save (int /*<<< orphan*/ *,struct net_buf_simple_state*) ; 
 int /*<<< orphan*/  ready_to_recv () ; 

void bt_mesh_net_recv(struct net_buf_simple *data, s8_t rssi,
                      enum bt_mesh_net_if net_if)
{
    NET_BUF_SIMPLE_DEFINE(buf, 29);
    struct bt_mesh_net_rx rx = { .rssi = rssi };
    struct net_buf_simple_state state;

    BT_DBG("rssi %d net_if %u", rssi, net_if);

    if (!ready_to_recv()) {
        return;
    }

    if (bt_mesh_net_decode(data, net_if, &rx, &buf)) {
        return;
    }

    /* Save the state so the buffer can later be relayed */
    net_buf_simple_save(&buf, &state);

#if CONFIG_BLE_MESH_NODE
    if (bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_SERVER) &&
                net_if == BLE_MESH_NET_IF_PROXY) {
            bt_mesh_proxy_addr_add(data, rx.ctx.addr);
        }
    }
#endif

    rx.local_match = (bt_mesh_fixed_group_match(rx.ctx.recv_dst) ||
                      bt_mesh_elem_find(rx.ctx.recv_dst));

    /* The transport layer has indicated that it has rejected the message,
    * but would like to see it again if it is received in the future.
    * This can happen if a message is received when the device is in
    * Low Power mode, but the message was not encrypted with the friend
    * credentials. Remove it from the message cache so that we accept
    * it again in the future.
    */
    if (bt_mesh_trans_recv(&buf, &rx) == -EAGAIN) {
        BT_WARN("Removing rejected message from Network Message Cache");
        msg_cache[rx.msg_cache_idx] = 0ULL;
        /* Rewind the next index now that we're not using this entry */
        msg_cache_next = rx.msg_cache_idx;
    }

    /* Relay if this was a group/virtual address, or if the destination
     * was neither a local element nor an LPN we're Friends for.
     */
#if CONFIG_BLE_MESH_NODE
    if (bt_mesh_is_provisioned()) {
        if (!BLE_MESH_ADDR_IS_UNICAST(rx.ctx.recv_dst) ||
                (!rx.local_match && !rx.friend_match)) {
            net_buf_simple_restore(&buf, &state);
            bt_mesh_net_relay(&buf, &rx);
        }
    }
#endif
}