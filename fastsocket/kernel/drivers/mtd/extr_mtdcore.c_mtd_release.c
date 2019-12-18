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
struct device {int dummy; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ MTD_DEVT (int /*<<< orphan*/ ) ; 
 TYPE_1__* dev_to_mtd (struct device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtd_class ; 

__attribute__((used)) static void mtd_release(struct device *dev)
{
	dev_t index = MTD_DEVT(dev_to_mtd(dev)->index);

	/* remove /dev/mtdXro node if needed */
	if (index)
		device_destroy(&mtd_class, index + 1);
}