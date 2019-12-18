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
struct synaptics_i2c {int scan_ms; int scan_rate_param; } ;

/* Variables and functions */
 int MSEC_PER_SEC ; 

__attribute__((used)) static inline void set_scan_rate(struct synaptics_i2c *touch, int scan_rate)
{
	touch->scan_ms = MSEC_PER_SEC / scan_rate;
	touch->scan_rate_param = scan_rate;
}