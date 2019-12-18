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
struct TYPE_2__ {int /*<<< orphan*/  local_work; int /*<<< orphan*/  ivu_timer; } ;

/* Variables and functions */
 TYPE_1__ bt_mesh ; 
 int /*<<< orphan*/  bt_mesh_net_local ; 
 int /*<<< orphan*/  ivu_refresh ; 
 int /*<<< orphan*/  k_delayed_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bt_mesh_net_init(void)
{
    k_delayed_work_init(&bt_mesh.ivu_timer, ivu_refresh);

    k_work_init(&bt_mesh.local_work, bt_mesh_net_local);
}