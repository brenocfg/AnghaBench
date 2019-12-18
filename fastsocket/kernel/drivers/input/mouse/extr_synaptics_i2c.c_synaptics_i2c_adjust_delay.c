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
struct synaptics_i2c {unsigned long scan_ms; unsigned long no_data_count; } ;

/* Variables and functions */
 unsigned long NO_DATA_SLEEP_MSECS ; 
 unsigned long NO_DATA_THRES ; 
 unsigned long THREAD_IRQ_SLEEP_MSECS ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 scalar_t__ polling_req ; 
 unsigned long round_jiffies_relative (unsigned long) ; 

unsigned long synaptics_i2c_adjust_delay(struct synaptics_i2c *touch,
					 bool have_data)
{
	unsigned long delay, nodata_count_thres;

	if (polling_req) {
		delay = touch->scan_ms;
		if (have_data) {
			touch->no_data_count = 0;
		} else {
			nodata_count_thres = NO_DATA_THRES / touch->scan_ms;
			if (touch->no_data_count < nodata_count_thres)
				touch->no_data_count++;
			else
				delay = NO_DATA_SLEEP_MSECS;
		}
		return msecs_to_jiffies(delay);
	} else {
		delay = msecs_to_jiffies(THREAD_IRQ_SLEEP_MSECS);
		return round_jiffies_relative(delay);
	}
}