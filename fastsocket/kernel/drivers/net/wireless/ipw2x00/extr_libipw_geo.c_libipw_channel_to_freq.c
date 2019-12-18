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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ bg_channels; scalar_t__ a_channels; } ;
struct libipw_device {TYPE_1__ geo; } ;
struct libipw_channel {int /*<<< orphan*/  freq; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct libipw_channel* libipw_get_channel (struct libipw_device*,int /*<<< orphan*/ ) ; 

u32 libipw_channel_to_freq(struct libipw_device * ieee, u8 channel)
{
	const struct libipw_channel * ch;

	/* Driver needs to initialize the geography map before using
	 * these helper functions */
	if (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		return 0;

	ch = libipw_get_channel(ieee, channel);
	if (!ch->channel)
		return 0;
	return ch->freq;
}