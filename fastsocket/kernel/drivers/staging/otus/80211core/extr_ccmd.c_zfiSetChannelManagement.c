#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
struct TYPE_3__ {int EnableHT; } ;
struct TYPE_4__ {int BandWidth40; int ExtOffset; int /*<<< orphan*/  frequency; TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCoreSetFrequencyEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiSetChannelManagement(zdev_t *dev, u32_t setting)
{
	zmw_get_wlan_dev(dev);

	switch (setting) {
	case 1:
		wd->sta.EnableHT = 1;
		wd->BandWidth40 = 1;
		wd->ExtOffset   = 1;
		break;
	case 3:
		wd->sta.EnableHT = 1;
		wd->BandWidth40 = 1;
		wd->ExtOffset   = 3;
		break;
	case 0:
		wd->sta.EnableHT = 1;
		wd->BandWidth40 = 0;
		wd->ExtOffset   = 0;
		break;
	default:
		wd->BandWidth40 = 0;
		wd->ExtOffset   = 0;
		break;
	}

	zfCoreSetFrequencyEx(dev, wd->frequency, wd->BandWidth40,
							wd->ExtOffset, NULL);
}