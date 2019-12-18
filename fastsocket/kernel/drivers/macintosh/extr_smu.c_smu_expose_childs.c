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
struct work_struct {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* of_dev; int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_next_child (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_platform_device_create (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* smu ; 

__attribute__((used)) static void smu_expose_childs(struct work_struct *unused)
{
	struct device_node *np;

	for (np = NULL; (np = of_get_next_child(smu->of_node, np)) != NULL;)
		if (of_device_is_compatible(np, "smu-sensors"))
			of_platform_device_create(np, "smu-sensors",
						  &smu->of_dev->dev);
}