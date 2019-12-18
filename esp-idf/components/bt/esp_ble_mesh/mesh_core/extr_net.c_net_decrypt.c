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
typedef  int /*<<< orphan*/  u8_t ;
struct net_buf_simple {int /*<<< orphan*/  data; } ;
struct bt_mesh_subnet {int /*<<< orphan*/  net_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct bt_mesh_net_rx {int old_iv; scalar_t__ net_if; TYPE_1__ ctx; } ;
struct TYPE_4__ {int iv_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_ADDR_IS_UNICAST (int /*<<< orphan*/ ) ; 
 scalar_t__ BLE_MESH_NET_IF_ADV ; 
 scalar_t__ BLE_MESH_NET_IF_PROXY_CFG ; 
 int /*<<< orphan*/  BLE_MESH_NET_IVI_RX (struct bt_mesh_net_rx*) ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  BT_WARN (char*,...) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_PROXY ; 
 int EALREADY ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int IVI (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NID (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SRC (int /*<<< orphan*/ ) ; 
 TYPE_2__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 int bt_mesh_net_decrypt (int /*<<< orphan*/  const*,struct net_buf_simple*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bt_mesh_net_obfuscate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ msg_cache_match (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 
 int /*<<< orphan*/  net_buf_simple_add (struct net_buf_simple*,size_t) ; 
 int /*<<< orphan*/  net_buf_simple_reset (struct net_buf_simple*) ; 

__attribute__((used)) static int net_decrypt(struct bt_mesh_subnet *sub, const u8_t *enc,
                       const u8_t *priv, const u8_t *data,
                       size_t data_len, struct bt_mesh_net_rx *rx,
                       struct net_buf_simple *buf)
{
    BT_DBG("NID 0x%02x net_idx 0x%04x", NID(data), sub->net_idx);
    BT_DBG("IVI %u net->iv_index 0x%08x", IVI(data), bt_mesh.iv_index);

    rx->old_iv = (IVI(data) != (bt_mesh.iv_index & 0x01));

    net_buf_simple_reset(buf);
    memcpy(net_buf_simple_add(buf, data_len), data, data_len);

    if (bt_mesh_net_obfuscate(buf->data, BLE_MESH_NET_IVI_RX(rx), priv)) {
        return -ENOENT;
    }

    /* TODO: For provisioner, when a device is re-provisioned and start to
     * send the same message(e.g. cfg_appkey_add), the status message is easy
     * to be filtered here. So when a device is re-provisioned, the related
     * msg_cache should be cleared. Will do it later.
     */
    if (rx->net_if == BLE_MESH_NET_IF_ADV && msg_cache_match(rx, buf)) {
        BT_WARN("Duplicate found in Network Message Cache");
        return -EALREADY;
    }

    rx->ctx.addr = SRC(buf->data);
    if (!BLE_MESH_ADDR_IS_UNICAST(rx->ctx.addr)) {
        BT_WARN("Ignoring non-unicast src addr 0x%04x", rx->ctx.addr);
        return -EINVAL;
    }

    BT_DBG("src 0x%04x", rx->ctx.addr);

#if CONFIG_BLE_MESH_NODE
    if (bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_PROXY) &&
                rx->net_if == BLE_MESH_NET_IF_PROXY_CFG) {
            return bt_mesh_net_decrypt(enc, buf, BLE_MESH_NET_IVI_RX(rx),
                                       true);
        }
    }
#endif

    return bt_mesh_net_decrypt(enc, buf, BLE_MESH_NET_IVI_RX(rx), false);
}