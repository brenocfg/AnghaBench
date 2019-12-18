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
struct net_buf_simple {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct bt_mesh_msg_ctx {int /*<<< orphan*/  addr; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct bt_mesh_model {int dummy; } ;
struct bt_mesh_cfg_hb_sub_status {void* max; void* min; void* count; void* period; void* dst; void* src; void* status; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_client_cancel (struct bt_mesh_model*,struct bt_mesh_msg_ctx*,struct bt_mesh_cfg_hb_sub_status*,int) ; 
 void* net_buf_simple_pull_le16 (struct net_buf_simple*) ; 
 void* net_buf_simple_pull_u8 (struct net_buf_simple*) ; 

__attribute__((used)) static void hb_sub_status(struct bt_mesh_model *model,
                          struct bt_mesh_msg_ctx *ctx,
                          struct net_buf_simple *buf)
{
    struct bt_mesh_cfg_hb_sub_status status = {0};

    BT_DBG("net_idx 0x%04x app_idx 0x%04x src 0x%04x len %u: %s",
           ctx->net_idx, ctx->app_idx, ctx->addr, buf->len,
           bt_hex(buf->data, buf->len));

    status.status = net_buf_simple_pull_u8(buf);
    status.src    = net_buf_simple_pull_le16(buf);
    status.dst    = net_buf_simple_pull_le16(buf);
    status.period = net_buf_simple_pull_u8(buf);
    status.count  = net_buf_simple_pull_u8(buf);
    status.min    = net_buf_simple_pull_u8(buf);
    status.max    = net_buf_simple_pull_u8(buf);

    cfg_client_cancel(model, ctx, &status, sizeof(struct bt_mesh_cfg_hb_sub_status));
}