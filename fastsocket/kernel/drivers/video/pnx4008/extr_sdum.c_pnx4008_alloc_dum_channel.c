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
 int ENORESOURCESLEFT ; 
 int MAX_DUM_CHANNELS ; 
 TYPE_1__ dum_data ; 

int pnx4008_alloc_dum_channel(int dev_id)
{
	int i = 0;

	while ((i < MAX_DUM_CHANNELS) && (dum_data.fb_owning_channel[i] != -1))
		i++;

	if (i == MAX_DUM_CHANNELS)
		return -ENORESOURCESLEFT;
	else {
		dum_data.fb_owning_channel[i] = dev_id;
		return i;
	}
}