#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ieee80211_device {int dummy; } ;
struct TYPE_3__ {scalar_t__* channel_map; } ;
typedef  TYPE_1__* PRT_DOT11D_INFO ;

/* Variables and functions */
 TYPE_1__* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 size_t MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  printk (char*) ; 

int IsLegalChannel(
	struct ieee80211_device * dev,
	u8 channel
)
{
	PRT_DOT11D_INFO pDot11dInfo = GET_DOT11D_INFO(dev);

	if(MAX_CHANNEL_NUMBER < channel)
	{
		printk("IsLegalChannel(): Invalid Channel\n");
		return 0;
	}
	if(pDot11dInfo->channel_map[channel] > 0)
		return 1;
	return 0;
}