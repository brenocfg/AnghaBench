#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8_t ;
typedef  int u64_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int u16_t ;
struct bt_mesh_subnet {int /*<<< orphan*/  net_idx; } ;
struct bt_mesh_net_tx {int src; int /*<<< orphan*/  xmit; struct bt_mesh_msg_ctx* ctx; struct bt_mesh_subnet* sub; } ;
struct bt_mesh_msg_ctx {int addr; int send_ttl; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_ADDR_IS_UNICAST (int) ; 
 int /*<<< orphan*/  BLE_MESH_KEY_UNUSED ; 
 int /*<<< orphan*/  BT_DBG (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT_WARN (char*) ; 
 int /*<<< orphan*/  TRANS_CTL_OP_ACK ; 
 int bt_mesh_ctl_send (struct bt_mesh_net_tx*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bt_mesh_lpn_established () ; 
 int /*<<< orphan*/  bt_mesh_net_transmit_get () ; 
 int bt_mesh_primary_addr () ; 
 int /*<<< orphan*/  sys_put_be16 (int,int*) ; 
 int /*<<< orphan*/  sys_put_be32 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int send_ack(struct bt_mesh_subnet *sub, u16_t src, u16_t dst,
                    u8_t ttl, u64_t *seq_auth, u32_t block, u8_t obo)
{
    struct bt_mesh_msg_ctx ctx = {
        .net_idx = sub->net_idx,
        .app_idx = BLE_MESH_KEY_UNUSED,
        .addr = dst,
        .send_ttl = ttl,
    };
    struct bt_mesh_net_tx tx = {
        .sub = sub,
        .ctx = &ctx,
        .src = obo ? bt_mesh_primary_addr() : src,
        .xmit = bt_mesh_net_transmit_get(),
    };
    u16_t seq_zero = *seq_auth & 0x1fff;
    u8_t buf[6];

    BT_DBG("SeqZero 0x%04x Block 0x%08x OBO %u", seq_zero, block, obo);

    if (bt_mesh_lpn_established()) {
        BT_WARN("Not sending ack when LPN is enabled");
        return 0;
    }

    /* This can happen if the segmented message was destined for a group
     * or virtual address.
     */
    if (!BLE_MESH_ADDR_IS_UNICAST(src)) {
        BT_WARN("Not sending ack for non-unicast address");
        return 0;
    }

    sys_put_be16(((seq_zero << 2) & 0x7ffc) | (obo << 15), buf);
    sys_put_be32(block, &buf[2]);

    return bt_mesh_ctl_send(&tx, TRANS_CTL_OP_ACK, buf, sizeof(buf),
                            NULL, NULL, NULL);
}