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
struct platform_device {int /*<<< orphan*/  name; TYPE_1__* id_entry; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_MODULE_PREFIX ; 
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int platform_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct platform_device	*pdev = to_platform_device(dev);

	add_uevent_var(env, "MODALIAS=%s%s", PLATFORM_MODULE_PREFIX,
		(pdev->id_entry) ? pdev->id_entry->name : pdev->name);
	return 0;
}