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
 int /*<<< orphan*/  OP_MOD_SUB_ADD ; 
 int mod_sub (int /*<<< orphan*/ ,struct bt_mesh_msg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bt_mesh_cfg_mod_sub_add(struct bt_mesh_msg_ctx *ctx, u16_t elem_addr,
                            u16_t sub_addr, u16_t mod_id, u16_t cid)
{
    if (!ctx || !ctx->addr) {
        return -EINVAL;
    }
    return mod_sub(OP_MOD_SUB_ADD, ctx, elem_addr, sub_addr, mod_id, cid);
}