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
struct prod_dev_id {scalar_t__ product_id; scalar_t__ device_id; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ product_id; scalar_t__ device_id; } ;
struct bmc_device {TYPE_1__ id; } ;

/* Variables and functions */
 struct bmc_device* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int __find_bmc_prod_dev_id(struct device *dev, void *data)
{
	struct prod_dev_id *id = data;
	struct bmc_device *bmc = dev_get_drvdata(dev);

	return (bmc->id.product_id == id->product_id
		&& bmc->id.device_id == id->device_id);
}