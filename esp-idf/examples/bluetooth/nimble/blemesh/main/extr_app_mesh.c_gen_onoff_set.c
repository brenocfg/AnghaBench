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
struct os_mbuf {int /*<<< orphan*/ * om_data; } ;
struct bt_mesh_msg_ctx {int dummy; } ;
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gen_on_off_state ; 
 int /*<<< orphan*/  gen_onoff_status (struct bt_mesh_model*,struct bt_mesh_msg_ctx*) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static void gen_onoff_set(struct bt_mesh_model *model,
                          struct bt_mesh_msg_ctx *ctx,
                          struct os_mbuf *buf)
{
    ESP_LOGI(tag, "#mesh-onoff SET\n");

    gen_on_off_state = buf->om_data[0];

    gen_onoff_status(model, ctx);
}