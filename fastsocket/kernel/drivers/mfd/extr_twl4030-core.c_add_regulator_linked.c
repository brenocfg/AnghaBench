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
struct regulator_init_data {unsigned int num_consumer_supplies; struct regulator_consumer_supply* consumer_supplies; } ;
struct regulator_consumer_supply {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* add_numbered_child (int,char*,int,struct regulator_init_data*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *
add_regulator_linked(int num, struct regulator_init_data *pdata,
		struct regulator_consumer_supply *consumers,
		unsigned num_consumers)
{
	/* regulator framework demands init_data ... */
	if (!pdata)
		return NULL;

	if (consumers) {
		pdata->consumer_supplies = consumers;
		pdata->num_consumer_supplies = num_consumers;
	}

	/* NOTE:  we currently ignore regulator IRQs, e.g. for short circuits */
	return add_numbered_child(3, "twl4030_reg", num,
		pdata, sizeof(*pdata), false, 0, 0);
}