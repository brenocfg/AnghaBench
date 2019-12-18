#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {TYPE_2__* a; TYPE_1__* bg; } ;
struct libipw_device {TYPE_3__ geo; } ;
struct TYPE_5__ {scalar_t__ flags; } ;
struct TYPE_4__ {scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ LIBIPW_24GHZ_CHANNELS ; 
 scalar_t__ LIBIPW_CH_INVALID ; 
 int libipw_channel_to_index (struct libipw_device*,scalar_t__) ; 

u8 libipw_get_channel_flags(struct libipw_device * ieee, u8 channel)
{
	int index = libipw_channel_to_index(ieee, channel);

	if (index == -1)
		return LIBIPW_CH_INVALID;

	if (channel <= LIBIPW_24GHZ_CHANNELS)
		return ieee->geo.bg[index].flags;

	return ieee->geo.a[index].flags;
}