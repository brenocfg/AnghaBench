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
struct enic {int /*<<< orphan*/  devcmd_lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vnic_dev_enable2 (int /*<<< orphan*/ ,int) ; 

int enic_dev_enable2(struct enic *enic, int active)
{
	int err;

	spin_lock(&enic->devcmd_lock);
	err = vnic_dev_enable2(enic->vdev, active);
	spin_unlock(&enic->devcmd_lock);

	return err;
}