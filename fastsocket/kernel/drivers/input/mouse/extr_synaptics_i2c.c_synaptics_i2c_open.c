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
struct synaptics_i2c {int /*<<< orphan*/  client; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_DATA_SLEEP_MSECS ; 
 struct synaptics_i2c* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ polling_req ; 
 int /*<<< orphan*/  synaptics_i2c_reschedule_work (struct synaptics_i2c*,int /*<<< orphan*/ ) ; 
 int synaptics_i2c_reset_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synaptics_i2c_open(struct input_dev *input)
{
	struct synaptics_i2c *touch = input_get_drvdata(input);
	int ret;

	ret = synaptics_i2c_reset_config(touch->client);
	if (ret)
		return ret;

	if (polling_req)
		synaptics_i2c_reschedule_work(touch,
				msecs_to_jiffies(NO_DATA_SLEEP_MSECS));

	return 0;
}