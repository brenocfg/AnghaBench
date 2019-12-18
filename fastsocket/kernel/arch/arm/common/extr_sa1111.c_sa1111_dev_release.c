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
struct sa1111_dev {int /*<<< orphan*/  res; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sa1111_dev* SA1111_DEV (struct device*) ; 
 int /*<<< orphan*/  kfree (struct sa1111_dev*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sa1111_dev_release(struct device *_dev)
{
	struct sa1111_dev *dev = SA1111_DEV(_dev);

	release_resource(&dev->res);
	kfree(dev);
}