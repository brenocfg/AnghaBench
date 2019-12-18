#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pmu {TYPE_1__* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  attr_groups; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct pmu*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_bus ; 
 int /*<<< orphan*/  pmu_dev_release ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int pmu_dev_alloc(struct pmu *pmu)
{
	int ret = -ENOMEM;

	pmu->dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!pmu->dev)
		goto out;

	pmu->dev->groups = pmu->attr_groups;
	device_initialize(pmu->dev);
	ret = dev_set_name(pmu->dev, "%s", pmu->name);
	if (ret)
		goto free_dev;

	dev_set_drvdata(pmu->dev, pmu);
	pmu->dev->bus = &pmu_bus;
	pmu->dev->release = pmu_dev_release;
	ret = device_add(pmu->dev);
	if (ret)
		goto free_dev;

out:
	return ret;

free_dev:
	put_device(pmu->dev);
	goto out;
}