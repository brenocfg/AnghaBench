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
struct of_device_id {int dummy; } ;
struct of_device {int dummy; } ;
struct TYPE_2__ {struct of_device* of_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_1__* smu ; 
 int /*<<< orphan*/  smu_expose_childs_work ; 

__attribute__((used)) static int smu_platform_probe(struct of_device* dev,
			      const struct of_device_id *match)
{
	if (!smu)
		return -ENODEV;
	smu->of_dev = dev;

	/*
	 * Ok, we are matched, now expose all i2c busses. We have to defer
	 * that unfortunately or it would deadlock inside the device model
	 */
	schedule_work(&smu_expose_childs_work);

	return 0;
}