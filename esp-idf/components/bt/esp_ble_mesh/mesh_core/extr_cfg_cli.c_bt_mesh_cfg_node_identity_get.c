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
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_msg_ctx {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OP_NODE_IDENTITY_GET ; 
 int node_identity_op (int /*<<< orphan*/ ,struct bt_mesh_msg_ctx*,int /*<<< orphan*/ ,int) ; 

int bt_mesh_cfg_node_identity_get(struct bt_mesh_msg_ctx *ctx, u16_t net_idx)
{
    if (!ctx || !ctx->addr) {
        return -EINVAL;
    }
    return node_identity_op(OP_NODE_IDENTITY_GET, ctx, net_idx, 0xFF);
}