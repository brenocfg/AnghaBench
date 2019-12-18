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
typedef  int u8_t ;
typedef  scalar_t__ u16_t ;
struct net_buf_simple {int dummy; } ;
struct bt_mesh_msg_ctx {int addr; } ;
struct bt_mesh_model {struct bt_mesh_cfg_srv* user_data; } ;
struct TYPE_2__ {unsigned int min_hops; unsigned int max_hops; unsigned int count; scalar_t__ expiry; scalar_t__ dst; scalar_t__ src; } ;
struct bt_mesh_cfg_srv {TYPE_1__ hb_sub; } ;
typedef  int s32_t ;

/* Variables and functions */
 scalar_t__ BLE_MESH_ADDR_IS_RFU (scalar_t__) ; 
 scalar_t__ BLE_MESH_ADDR_IS_UNICAST (scalar_t__) ; 
 scalar_t__ BLE_MESH_ADDR_IS_VIRTUAL (scalar_t__) ; 
 scalar_t__ BLE_MESH_ADDR_UNASSIGNED ; 
 void* BLE_MESH_TTL_MAX ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  BT_WARN (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ bt_mesh_primary_addr () ; 
 int /*<<< orphan*/  bt_mesh_set_hb_sub_dst (scalar_t__) ; 
 unsigned int hb_pwr2 (int,int) ; 
 int /*<<< orphan*/  hb_sub_send_status (struct bt_mesh_model*,struct bt_mesh_msg_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ k_uptime_get () ; 
 scalar_t__ net_buf_simple_pull_le16 (struct net_buf_simple*) ; 
 int net_buf_simple_pull_u8 (struct net_buf_simple*) ; 

__attribute__((used)) static void heartbeat_sub_set(struct bt_mesh_model *model,
                              struct bt_mesh_msg_ctx *ctx,
                              struct net_buf_simple *buf)
{
    struct bt_mesh_cfg_srv *cfg = model->user_data;
    u16_t sub_src, sub_dst;
    u8_t sub_period;
    s32_t period_ms;

    BT_DBG("src 0x%04x", ctx->addr);

    sub_src = net_buf_simple_pull_le16(buf);
    sub_dst = net_buf_simple_pull_le16(buf);
    sub_period = net_buf_simple_pull_u8(buf);

    BT_DBG("sub_src 0x%04x sub_dst 0x%04x period 0x%02x",
           sub_src, sub_dst, sub_period);

    if (sub_src != BLE_MESH_ADDR_UNASSIGNED &&
            !BLE_MESH_ADDR_IS_UNICAST(sub_src)) {
        BT_WARN("Prohibited source address");
        return;
    }

    if (BLE_MESH_ADDR_IS_VIRTUAL(sub_dst) || BLE_MESH_ADDR_IS_RFU(sub_dst) ||
            (BLE_MESH_ADDR_IS_UNICAST(sub_dst) &&
             sub_dst != bt_mesh_primary_addr())) {
        BT_WARN("Prohibited destination address");
        return;
    }

    if (sub_period > 0x11) {
        BT_WARN("Prohibited subscription period 0x%02x", sub_period);
        return;
    }

    if (sub_src == BLE_MESH_ADDR_UNASSIGNED ||
            sub_dst == BLE_MESH_ADDR_UNASSIGNED ||
            sub_period == 0x00) {
        /* Only an explicit address change to unassigned should
         * trigger clearing of the values according to
         * MESH/NODE/CFG/HBS/BV-02-C.
         */
        if (sub_src == BLE_MESH_ADDR_UNASSIGNED ||
                sub_dst == BLE_MESH_ADDR_UNASSIGNED) {
            cfg->hb_sub.src = BLE_MESH_ADDR_UNASSIGNED;
            cfg->hb_sub.dst = BLE_MESH_ADDR_UNASSIGNED;
            cfg->hb_sub.min_hops = BLE_MESH_TTL_MAX;
            cfg->hb_sub.max_hops = 0U;
            cfg->hb_sub.count = 0U;
        }

        period_ms = 0;
    } else {
        cfg->hb_sub.src = sub_src;
        cfg->hb_sub.dst = sub_dst;
        cfg->hb_sub.min_hops = BLE_MESH_TTL_MAX;
        cfg->hb_sub.max_hops = 0U;
        cfg->hb_sub.count = 0U;
        period_ms = hb_pwr2(sub_period, 1) * 1000U;
    }

    /* Let the transport layer know it needs to handle this address */
    bt_mesh_set_hb_sub_dst(cfg->hb_sub.dst);

    BT_DBG("period_ms %u", period_ms);

    if (period_ms) {
        cfg->hb_sub.expiry = k_uptime_get() + period_ms;
    } else {
        cfg->hb_sub.expiry = 0;
    }

    hb_sub_send_status(model, ctx, STATUS_SUCCESS);

    /* MESH/NODE/CFG/HBS/BV-01-C expects the MinHops to be 0x7f after
     * disabling subscription, but 0x00 for subsequent Get requests.
     */
    if (!period_ms) {
        cfg->hb_sub.min_hops = 0U;
    }
}