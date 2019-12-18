#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_5__ {int ChannelInfo; } ;
struct TYPE_6__ {TYPE_1__ HtInfo; } ;
struct TYPE_7__ {TYPE_2__ ie; } ;
struct TYPE_8__ {TYPE_3__ sta; } ;

/* Variables and functions */
 int ExtHtCap_RIFSMode ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiCheckRifs(zdev_t *dev)
{
	zmw_get_wlan_dev(dev);

	if (wd->sta.ie.HtInfo.ChannelInfo & ExtHtCap_RIFSMode)
		;
		/* zfHpSetRifs(dev, wd->sta.EnableHT, wd->sta.HT2040,
		*  (wd->sta.currentFrequency < 3000)? 1:0);
		*/
}