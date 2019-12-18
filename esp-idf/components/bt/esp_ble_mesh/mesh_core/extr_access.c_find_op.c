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
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_model_op {scalar_t__ opcode; scalar_t__ func; } ;
struct bt_mesh_model {struct bt_mesh_model_op* op; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_ADDR_IS_GROUP (int /*<<< orphan*/ ) ; 
 scalar_t__ BLE_MESH_ADDR_IS_VIRTUAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_model_find_group (struct bt_mesh_model*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  model_has_key (struct bt_mesh_model*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct bt_mesh_model_op *find_op(struct bt_mesh_model *models,
        u8_t model_count, u16_t dst,
        u16_t app_idx, u32_t opcode,
        struct bt_mesh_model **model)
{
    u8_t i;

    for (i = 0U; i < model_count; i++) {
        const struct bt_mesh_model_op *op;

        *model = &models[i];

        if (BLE_MESH_ADDR_IS_GROUP(dst) ||
                BLE_MESH_ADDR_IS_VIRTUAL(dst)) {
            if (!bt_mesh_model_find_group(*model, dst)) {
                continue;
            }
        }

        if (!model_has_key(*model, app_idx)) {
            continue;
        }

        for (op = (*model)->op; op->func; op++) {
            if (op->opcode == opcode) {
                return op;
            }
        }
    }

    *model = NULL;
    return NULL;
}