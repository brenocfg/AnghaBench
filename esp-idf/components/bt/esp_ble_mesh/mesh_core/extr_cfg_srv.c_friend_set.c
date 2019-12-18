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
struct net_buf_simple {int* data; int /*<<< orphan*/  len; } ;
struct bt_mesh_msg_ctx {int /*<<< orphan*/  addr; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct bt_mesh_model {struct bt_mesh_cfg_srv* user_data; } ;
struct TYPE_2__ {int feat; } ;
struct bt_mesh_cfg_srv {int frnd; TYPE_1__ hb_pub; } ;

/* Variables and functions */
 int BLE_MESH_FEAT_FRIEND ; 
 int BLE_MESH_FRIEND_DISABLED ; 
 int /*<<< orphan*/  BLE_MESH_KEY_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*,int,int,...) ; 
 int /*<<< orphan*/  BT_WARN (char*,...) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_friend_clear_net_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_heartbeat_send () ; 
 int /*<<< orphan*/  bt_mesh_store_cfg () ; 
 int /*<<< orphan*/  send_friend_status (struct bt_mesh_model*,struct bt_mesh_msg_ctx*) ; 

__attribute__((used)) static void friend_set(struct bt_mesh_model *model,
                       struct bt_mesh_msg_ctx *ctx,
                       struct net_buf_simple *buf)
{
    struct bt_mesh_cfg_srv *cfg = model->user_data;

    BT_DBG("net_idx 0x%04x app_idx 0x%04x src 0x%04x len %u: %s",
           ctx->net_idx, ctx->app_idx, ctx->addr, buf->len,
           bt_hex(buf->data, buf->len));

    if (buf->data[0] != 0x00 && buf->data[0] != 0x01) {
        BT_WARN("Invalid Friend value 0x%02x", buf->data[0]);
        return;
    }

    if (!cfg) {
        BT_WARN("No Configuration Server context available");
        goto send_status;
    }

    BT_DBG("Friend 0x%02x -> 0x%02x", cfg->frnd, buf->data[0]);

    if (cfg->frnd == buf->data[0]) {
        goto send_status;
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND)) {
        cfg->frnd = buf->data[0];

        if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
            bt_mesh_store_cfg();
        }

        if (cfg->frnd == BLE_MESH_FRIEND_DISABLED) {
            bt_mesh_friend_clear_net_idx(BLE_MESH_KEY_ANY);
        }
    }

    if (cfg->hb_pub.feat & BLE_MESH_FEAT_FRIEND) {
        bt_mesh_heartbeat_send();
    }

send_status:
    send_friend_status(model, ctx);
}