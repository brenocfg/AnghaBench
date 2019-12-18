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
struct TYPE_3__ {struct device_node* node; } ;
struct TYPE_4__ {TYPE_1__ ofdev; } ;
struct i2sbus_dev {int bus_number; int /*<<< orphan*/  item; void* clock_disable; void* cell_disable; void* clock_enable; void* cell_enable; void* enable; TYPE_2__ sound; } ;
struct i2sbus_control {int /*<<< orphan*/  list; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pmf_find_function (struct device_node*,char*) ; 
 int /*<<< orphan*/  pmf_put_function (void*) ; 

int i2sbus_control_add_dev(struct i2sbus_control *c,
			   struct i2sbus_dev *i2sdev)
{
	struct device_node *np;

	np = i2sdev->sound.ofdev.node;
	i2sdev->enable = pmf_find_function(np, "enable");
	i2sdev->cell_enable = pmf_find_function(np, "cell-enable");
	i2sdev->clock_enable = pmf_find_function(np, "clock-enable");
	i2sdev->cell_disable = pmf_find_function(np, "cell-disable");
	i2sdev->clock_disable = pmf_find_function(np, "clock-disable");

	/* if the bus number is not 0 or 1 we absolutely need to use
	 * the platform functions -- there's nothing in Darwin that
	 * would allow seeing a system behind what the FCRs are then,
	 * and I don't want to go parsing a bunch of platform functions
	 * by hand to try finding a system... */
	if (i2sdev->bus_number != 0 && i2sdev->bus_number != 1 &&
	    (!i2sdev->enable ||
	     !i2sdev->cell_enable || !i2sdev->clock_enable ||
	     !i2sdev->cell_disable || !i2sdev->clock_disable)) {
		pmf_put_function(i2sdev->enable);
		pmf_put_function(i2sdev->cell_enable);
		pmf_put_function(i2sdev->clock_enable);
		pmf_put_function(i2sdev->cell_disable);
		pmf_put_function(i2sdev->clock_disable);
		return -ENODEV;
	}

	list_add(&i2sdev->item, &c->list);

	return 0;
}