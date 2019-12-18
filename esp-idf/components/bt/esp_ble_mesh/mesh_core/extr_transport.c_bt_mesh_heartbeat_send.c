#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct __packed   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  unsigned int u16_t ;
struct bt_mesh_net_tx {int /*<<< orphan*/  xmit; int /*<<< orphan*/  src; struct bt_mesh_msg_ctx* ctx; int /*<<< orphan*/  sub; } ;
struct bt_mesh_msg_ctx {scalar_t__ addr; int /*<<< orphan*/  send_ttl; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct TYPE_4__ {scalar_t__ dst; int /*<<< orphan*/  ttl; int /*<<< orphan*/  net_idx; } ;
struct bt_mesh_cfg_srv {TYPE_1__ hb_pub; int /*<<< orphan*/  model; } ;
typedef  int /*<<< orphan*/  hb ;
struct __packed {int /*<<< orphan*/  init_ttl; unsigned int feat; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_ADDR_UNASSIGNED ; 
 unsigned int BLE_MESH_FEAT_FRIEND ; 
 unsigned int BLE_MESH_FEAT_LOW_POWER ; 
 unsigned int BLE_MESH_FEAT_PROXY ; 
 unsigned int BLE_MESH_FEAT_RELAY ; 
 scalar_t__ BLE_MESH_FRIEND_ENABLED ; 
 scalar_t__ BLE_MESH_GATT_PROXY_ENABLED ; 
 int /*<<< orphan*/  BLE_MESH_KEY_UNUSED ; 
 scalar_t__ BLE_MESH_RELAY_ENABLED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TRANS_CTL_OP_HEARTBEAT ; 
 struct bt_mesh_cfg_srv* bt_mesh_cfg_get () ; 
 int /*<<< orphan*/  bt_mesh_ctl_send (struct bt_mesh_net_tx*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bt_mesh_friend_get () ; 
 scalar_t__ bt_mesh_gatt_proxy_get () ; 
 scalar_t__ bt_mesh_lpn_established () ; 
 TYPE_2__* bt_mesh_model_elem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_net_transmit_get () ; 
 scalar_t__ bt_mesh_relay_get () ; 
 int /*<<< orphan*/  bt_mesh_subnet_get (int /*<<< orphan*/ ) ; 
 unsigned int sys_cpu_to_be16 (unsigned int) ; 

void bt_mesh_heartbeat_send(void)
{
    struct bt_mesh_cfg_srv *cfg = bt_mesh_cfg_get();
    u16_t feat = 0U;
    struct __packed {
        u8_t  init_ttl;
        u16_t feat;
    } hb;
    struct bt_mesh_msg_ctx ctx = {
        .net_idx = cfg->hb_pub.net_idx,
        .app_idx = BLE_MESH_KEY_UNUSED,
        .addr = cfg->hb_pub.dst,
        .send_ttl = cfg->hb_pub.ttl,
    };
    struct bt_mesh_net_tx tx = {
        .sub = bt_mesh_subnet_get(cfg->hb_pub.net_idx),
        .ctx = &ctx,
        .src = bt_mesh_model_elem(cfg->model)->addr,
        .xmit = bt_mesh_net_transmit_get(),
    };

    /* Do nothing if heartbeat publication is not enabled */
    if (cfg->hb_pub.dst == BLE_MESH_ADDR_UNASSIGNED) {
        return;
    }

    hb.init_ttl = cfg->hb_pub.ttl;

    if (bt_mesh_relay_get() == BLE_MESH_RELAY_ENABLED) {
        feat |= BLE_MESH_FEAT_RELAY;
    }

    if (bt_mesh_gatt_proxy_get() == BLE_MESH_GATT_PROXY_ENABLED) {
        feat |= BLE_MESH_FEAT_PROXY;
    }

    if (bt_mesh_friend_get() == BLE_MESH_FRIEND_ENABLED) {
        feat |= BLE_MESH_FEAT_FRIEND;
    }

    if (bt_mesh_lpn_established()) {
        feat |= BLE_MESH_FEAT_LOW_POWER;
    }

    hb.feat = sys_cpu_to_be16(feat);

    BT_DBG("InitTTL %u feat 0x%04x", cfg->hb_pub.ttl, feat);

    bt_mesh_ctl_send(&tx, TRANS_CTL_OP_HEARTBEAT, &hb, sizeof(hb),
                     NULL, NULL, NULL);
}