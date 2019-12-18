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
struct mc13783 {unsigned int ts_active; } ;

/* Variables and functions */

void mc13783_adc_set_ts_status(struct mc13783 *mc13783, unsigned int status)
{
	mc13783->ts_active = status;
}