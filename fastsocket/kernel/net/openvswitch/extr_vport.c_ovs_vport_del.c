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
struct vport {TYPE_1__* ops; int /*<<< orphan*/  hash_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct vport*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_OVSL () ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vport*) ; 

void ovs_vport_del(struct vport *vport)
{
	ASSERT_OVSL();

	hlist_del_rcu(&vport->hash_node);

	vport->ops->destroy(vport);
}