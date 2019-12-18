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
struct virtual_consumer_data {scalar_t__ min_uV; scalar_t__ max_uV; int enabled; int /*<<< orphan*/  regulator; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void update_voltage_constraints(struct device *dev,
				       struct virtual_consumer_data *data)
{
	int ret;

	if (data->min_uV && data->max_uV
	    && data->min_uV <= data->max_uV) {
		dev_dbg(dev, "Requesting %d-%duV\n",
			data->min_uV, data->max_uV);
		ret = regulator_set_voltage(data->regulator,
					data->min_uV, data->max_uV);
		if (ret != 0) {
			dev_err(dev,
				"regulator_set_voltage() failed: %d\n", ret);
			return;
		}
	}

	if (data->min_uV && data->max_uV && !data->enabled) {
		dev_dbg(dev, "Enabling regulator\n");
		ret = regulator_enable(data->regulator);
		if (ret == 0)
			data->enabled = 1;
		else
			dev_err(dev, "regulator_enable() failed: %d\n",
				ret);
	}

	if (!(data->min_uV && data->max_uV) && data->enabled) {
		dev_dbg(dev, "Disabling regulator\n");
		ret = regulator_disable(data->regulator);
		if (ret == 0)
			data->enabled = 0;
		else
			dev_err(dev, "regulator_disable() failed: %d\n",
				ret);
	}
}