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
struct bt_mesh_msg_ctx {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OP_NET_TRANSMIT_GET ; 
 int get_state_u8 (struct bt_mesh_msg_ctx*,int /*<<< orphan*/ ) ; 

int bt_mesh_cfg_net_transmit_get(struct bt_mesh_msg_ctx *ctx)
{
    if (!ctx || !ctx->addr) {
        return -EINVAL;
    }
    return get_state_u8(ctx, OP_NET_TRANSMIT_GET);
}