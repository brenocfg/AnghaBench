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
typedef  scalar_t__ u_int64_t ;

/* Variables and functions */
 scalar_t__ IFQ_UPDATE_INTERVAL ; 
 scalar_t__ ifclassq_update_interval ; 

void
ifclassq_calc_update_interval(u_int64_t *update_interval)
{
	u_int64_t uint = 0;

	/* If the system level override is set, use it */
	if (ifclassq_update_interval != 0)
		uint = ifclassq_update_interval;

	/* Otherwise use the default value */
	if (uint == 0)
		uint = IFQ_UPDATE_INTERVAL;

	*update_interval = uint;
}