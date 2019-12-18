#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32_t ;
struct TYPE_3__ {scalar_t__ cli_op; scalar_t__ status_op; } ;
typedef  TYPE_1__ bt_mesh_client_op_pair_t ;

/* Variables and functions */

__attribute__((used)) static u32_t bt_mesh_client_get_status_op(const bt_mesh_client_op_pair_t *op_pair,
        int size, u32_t opcode)
{
    if (!op_pair || size == 0) {
        return 0;
    }

    const bt_mesh_client_op_pair_t *op = op_pair;
    for (int i = 0; i < size; i++) {
        if (op->cli_op == opcode) {
            return op->status_op;
        }
        op++;
    }

    return 0;
}