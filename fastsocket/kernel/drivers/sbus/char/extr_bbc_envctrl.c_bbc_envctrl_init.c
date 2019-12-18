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
struct of_device {TYPE_1__* node; } ;
struct bbc_i2c_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attach_one_fan (struct bbc_i2c_bus*,struct of_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_one_temp (struct bbc_i2c_bus*,struct of_device*,int /*<<< orphan*/ ) ; 
 struct of_device* bbc_i2c_getdev (struct bbc_i2c_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenvctrld ; 
 int /*<<< orphan*/ * kenvctrld_task ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int bbc_envctrl_init(struct bbc_i2c_bus *bp)
{
	struct of_device *op;
	int temp_index = 0;
	int fan_index = 0;
	int devidx = 0;

	while ((op = bbc_i2c_getdev(bp, devidx++)) != NULL) {
		if (!strcmp(op->node->name, "temperature"))
			attach_one_temp(bp, op, temp_index++);
		if (!strcmp(op->node->name, "fan-control"))
			attach_one_fan(bp, op, fan_index++);
	}
	if (temp_index != 0 && fan_index != 0) {
		kenvctrld_task = kthread_run(kenvctrld, NULL, "kenvctrld");
		if (IS_ERR(kenvctrld_task)) {
			int err = PTR_ERR(kenvctrld_task);

			kenvctrld_task = NULL;
			return err;
		}
	}

	return 0;
}