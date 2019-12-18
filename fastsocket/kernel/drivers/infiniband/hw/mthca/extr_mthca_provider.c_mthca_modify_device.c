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
struct ib_device_modify {int /*<<< orphan*/  node_desc; } ;
struct ib_device {int /*<<< orphan*/  node_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_mask_mutex; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int IB_DEVICE_MODIFY_NODE_DESC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mthca_modify_device(struct ib_device *ibdev,
			       int mask,
			       struct ib_device_modify *props)
{
	if (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		return -EOPNOTSUPP;

	if (mask & IB_DEVICE_MODIFY_NODE_DESC) {
		if (mutex_lock_interruptible(&to_mdev(ibdev)->cap_mask_mutex))
			return -ERESTARTSYS;
		memcpy(ibdev->node_desc, props->node_desc, 64);
		mutex_unlock(&to_mdev(ibdev)->cap_mask_mutex);
	}

	return 0;
}