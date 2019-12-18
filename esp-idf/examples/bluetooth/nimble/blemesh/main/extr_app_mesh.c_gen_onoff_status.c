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
typedef  int /*<<< orphan*/  uint8_t ;
struct os_mbuf {int dummy; } ;
struct bt_mesh_msg_ctx {int dummy; } ;
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MESH_MODEL_OP_2 (int,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 struct os_mbuf* NET_BUF_SIMPLE (int) ; 
 int /*<<< orphan*/  bt_mesh_model_msg_init (struct os_mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_model_send (struct bt_mesh_model*,struct bt_mesh_msg_ctx*,struct os_mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_on_off_state ; 
 int /*<<< orphan*/ * net_buf_simple_add (struct os_mbuf*,int) ; 
 int /*<<< orphan*/  os_mbuf_free_chain (struct os_mbuf*) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static void gen_onoff_status(struct bt_mesh_model *model,
                             struct bt_mesh_msg_ctx *ctx)
{
    struct os_mbuf *msg = NET_BUF_SIMPLE(3);
    uint8_t *status;

    ESP_LOGI(tag, "#mesh-onoff STATUS\n");

    bt_mesh_model_msg_init(msg, BT_MESH_MODEL_OP_2(0x82, 0x04));
    status = net_buf_simple_add(msg, 1);
    *status = gen_on_off_state;

    if (bt_mesh_model_send(model, ctx, msg, NULL, NULL)) {
        ESP_LOGI(tag, "#mesh-onoff STATUS: send status failed\n");
    }

    os_mbuf_free_chain(msg);
}