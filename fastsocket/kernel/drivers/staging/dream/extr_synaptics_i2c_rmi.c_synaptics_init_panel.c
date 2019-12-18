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
struct synaptics_ts_data {int dummy; } ;

/* Variables and functions */
 int i2c_set (struct synaptics_ts_data*,int,int,char*) ; 

__attribute__((used)) static int synaptics_init_panel(struct synaptics_ts_data *ts)
{
	int ret;

	ret = i2c_set(ts, 0xff, 0x10, "set page select");
	if (ret == 0)
		ret = i2c_set(ts, 0x41, 0x04, "set No Clip Z");

	ret = i2c_set(ts, 0xff, 0x04, "fallback page select");
	ret = i2c_set(ts, 0xf0, 0x81, "select 80 reports per second");
	return ret;
}