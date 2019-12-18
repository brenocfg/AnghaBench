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
struct TYPE_2__ {int* fb_owning_channel; } ;

/* Variables and functions */
 int EFBNOTOWNER ; 
 int EINVAL ; 
 int MAX_DUM_CHANNELS ; 
 int /*<<< orphan*/  clear_channel (int) ; 
 TYPE_1__ dum_data ; 

int pnx4008_free_dum_channel(int channr, int dev_id)
{
	if (channr < 0 || channr > MAX_DUM_CHANNELS)
		return -EINVAL;
	else if (dum_data.fb_owning_channel[channr] != dev_id)
		return -EFBNOTOWNER;
	else {
		clear_channel(channr);
		dum_data.fb_owning_channel[channr] = -1;
	}

	return 0;
}