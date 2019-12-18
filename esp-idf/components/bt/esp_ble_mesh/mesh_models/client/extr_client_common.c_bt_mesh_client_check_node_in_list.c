#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16_t ;
typedef  int /*<<< orphan*/  sys_snode_t ;
typedef  int /*<<< orphan*/  sys_slist_t ;
struct TYPE_3__ {scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ ctx; } ;
typedef  TYPE_2__ bt_mesh_client_node_t ;

/* Variables and functions */
 scalar_t__ sys_slist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sys_slist_peek_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sys_slist_peek_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bt_mesh_client_check_node_in_list(sys_slist_t *list, u16_t tx_dst)
{
    if (sys_slist_is_empty(list)) {
        return false;
    }

    sys_snode_t *cur = NULL; bt_mesh_client_node_t *node = NULL;
    for (cur = sys_slist_peek_head(list);
            cur != NULL; cur = sys_slist_peek_next(cur)) {
        node = (bt_mesh_client_node_t *)cur;
        if (node->ctx.addr == tx_dst) {
            return true;
        }
    }

    return false;
}