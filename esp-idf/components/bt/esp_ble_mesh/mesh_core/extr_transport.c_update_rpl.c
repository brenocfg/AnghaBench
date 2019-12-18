#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bt_mesh_rpl {int /*<<< orphan*/  old_iv; int /*<<< orphan*/  seq; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct bt_mesh_net_rx {int /*<<< orphan*/  old_iv; int /*<<< orphan*/  seq; TYPE_1__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_store_rpl (struct bt_mesh_rpl*) ; 

__attribute__((used)) static void update_rpl(struct bt_mesh_rpl *rpl, struct bt_mesh_net_rx *rx)
{
    rpl->src = rx->ctx.addr;
    rpl->seq = rx->seq;
    rpl->old_iv = rx->old_iv;

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
        bt_mesh_store_rpl(rpl);
    }
}