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
struct os_mbuf {int dummy; } ;
struct bt_mesh_msg_ctx {int dummy; } ;
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MESH_MODEL_OP_2 (int,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 struct os_mbuf* NET_BUF_SIMPLE (int) ; 
 int /*<<< orphan*/  bt_mesh_model_msg_init (struct os_mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_model_send (struct bt_mesh_model*,struct bt_mesh_msg_ctx*,struct os_mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_level_state ; 
 int /*<<< orphan*/  net_buf_simple_add_le16 (struct os_mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_mbuf_free_chain (struct os_mbuf*) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static void gen_level_status(struct bt_mesh_model *model,
                             struct bt_mesh_msg_ctx *ctx)
{
    struct os_mbuf *msg = NET_BUF_SIMPLE(4);

    ESP_LOGI(tag, "#mesh-level STATUS\n");

    bt_mesh_model_msg_init(msg, BT_MESH_MODEL_OP_2(0x82, 0x08));
    net_buf_simple_add_le16(msg, gen_level_state);

    if (bt_mesh_model_send(model, ctx, msg, NULL, NULL)) {
        ESP_LOGI(tag, "#mesh-level STATUS: send status failed\n");
    }

    os_mbuf_free_chain(msg);
}