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
struct TYPE_4__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  res_id; int /*<<< orphan*/  release; int /*<<< orphan*/  rank; int /*<<< orphan*/  data_state; int /*<<< orphan*/  oper_state; int /*<<< orphan*/  persistence; } ;
struct scm_device {unsigned int nr_max_block; unsigned long size; int /*<<< orphan*/  lock; TYPE_2__ dev; TYPE_1__ attrs; scalar_t__ address; } ;
struct sale {int /*<<< orphan*/  rid; int /*<<< orphan*/  r; int /*<<< orphan*/  rank; int /*<<< orphan*/  data_state; int /*<<< orphan*/  op_state; int /*<<< orphan*/  p; scalar_t__ sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,unsigned long long) ; 
 int /*<<< orphan*/  scm_bus_type ; 
 int /*<<< orphan*/  scm_root ; 
 int /*<<< orphan*/  scmdev_attr_groups ; 
 int /*<<< orphan*/  scmdev_release ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scmdev_setup(struct scm_device *scmdev, struct sale *sale,
			 unsigned int size, unsigned int max_blk_count)
{
	dev_set_name(&scmdev->dev, "%016llx", (unsigned long long) sale->sa);
	scmdev->nr_max_block = max_blk_count;
	scmdev->address = sale->sa;
	scmdev->size = 1UL << size;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.persistence = sale->p;
	scmdev->attrs.oper_state = sale->op_state;
	scmdev->attrs.data_state = sale->data_state;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.release = sale->r;
	scmdev->attrs.res_id = sale->rid;
	scmdev->dev.parent = scm_root;
	scmdev->dev.bus = &scm_bus_type;
	scmdev->dev.release = scmdev_release;
	scmdev->dev.groups = scmdev_attr_groups;
	spin_lock_init(&scmdev->lock);
}