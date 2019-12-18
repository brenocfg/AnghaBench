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
typedef  scalar_t__ u16 ;
struct brcms_c_info {TYPE_1__* default_bss; } ;
struct TYPE_2__ {scalar_t__ beacon_period; } ;

/* Variables and functions */
 int EINVAL ; 

int brcms_c_set_beacon_period(struct brcms_c_info *wlc, u16 period)
{
	if (period == 0)
		return -EINVAL;

	wlc->default_bss->beacon_period = period;
	return 0;
}