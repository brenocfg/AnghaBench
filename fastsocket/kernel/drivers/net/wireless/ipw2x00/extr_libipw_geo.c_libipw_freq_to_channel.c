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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_6__ {int bg_channels; int a_channels; TYPE_2__* a; TYPE_1__* bg; } ;
struct libipw_device {int freq_band; TYPE_3__ geo; } ;
struct TYPE_5__ {int freq; int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int freq; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int LIBIPW_24GHZ_BAND ; 
 int LIBIPW_52GHZ_BAND ; 

u8 libipw_freq_to_channel(struct libipw_device * ieee, u32 freq)
{
	int i;

	/* Driver needs to initialize the geography map before using
	 * these helper functions */
	if (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		return 0;

	freq /= 100000;

	if (ieee->freq_band & LIBIPW_24GHZ_BAND)
		for (i = 0; i < ieee->geo.bg_channels; i++)
			if (ieee->geo.bg[i].freq == freq)
				return ieee->geo.bg[i].channel;

	if (ieee->freq_band & LIBIPW_52GHZ_BAND)
		for (i = 0; i < ieee->geo.a_channels; i++)
			if (ieee->geo.a[i].freq == freq)
				return ieee->geo.a[i].channel;

	return 0;
}