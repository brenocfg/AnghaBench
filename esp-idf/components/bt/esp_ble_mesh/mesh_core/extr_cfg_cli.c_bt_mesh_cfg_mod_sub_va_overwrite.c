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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_msg_ctx {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OP_MOD_SUB_VA_OVERWRITE ; 
 int mod_sub_va (int /*<<< orphan*/ ,struct bt_mesh_msg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bt_mesh_cfg_mod_sub_va_overwrite(struct bt_mesh_msg_ctx *ctx, u16_t elem_addr,
                                     const u8_t label[16], u16_t mod_id, u16_t cid)
{
    if (!ctx || !ctx->addr || !label) {
        return -EINVAL;
    }
    return mod_sub_va(OP_MOD_SUB_VA_OVERWRITE, ctx, elem_addr, label, mod_id, cid);
}