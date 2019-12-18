#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_iov_port {int /*<<< orphan*/  dentr_ar; TYPE_2__* dev; int /*<<< orphan*/  cur_port; int /*<<< orphan*/  mcgs_parent; int /*<<< orphan*/  pkeys_parent; int /*<<< orphan*/  gids_parent; int /*<<< orphan*/  admin_alias_parent; } ;
struct mlx4_ib_dev {struct mlx4_ib_iov_port* iov_ports; TYPE_3__* dev; } ;
struct TYPE_4__ {int num_ports; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  ports_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_is_master (TYPE_3__*) ; 

__attribute__((used)) static void unregister_alias_guid_tree(struct mlx4_ib_dev *device)
{
	struct mlx4_ib_iov_port *p;
	int i;

	if (!mlx4_is_master(device->dev))
		return;

	for (i = 0; i < device->dev->caps.num_ports; i++) {
		p = &device->iov_ports[i];
		kobject_put(p->admin_alias_parent);
		kobject_put(p->gids_parent);
		kobject_put(p->pkeys_parent);
		kobject_put(p->mcgs_parent);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->cur_port);
		kobject_put(p->dev->ports_parent);
		kfree(p->dentr_ar);
	}
}