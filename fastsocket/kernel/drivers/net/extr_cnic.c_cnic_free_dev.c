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
struct cnic_dev {int /*<<< orphan*/  netdev; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cnic_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cnic_free_dev(struct cnic_dev *dev)
{
	int i = 0;

	while ((atomic_read(&dev->ref_count) != 0) && i < 10) {
		msleep(100);
		i++;
	}
	if (atomic_read(&dev->ref_count) != 0)
		netdev_err(dev->netdev, "Failed waiting for ref count to go to zero\n");

	netdev_info(dev->netdev, "Removed CNIC device\n");
	dev_put(dev->netdev);
	kfree(dev);
}