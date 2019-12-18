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
struct ieee80211_device {int softmac_features; int scanning; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* start_scan ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  softmac_scan_wq; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_SCAN ; 
 scalar_t__ IS_COUNTRY_IE_VALID (struct ieee80211_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct ieee80211_device*) ; 
 int /*<<< orphan*/  RESET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ieee80211_start_scan(struct ieee80211_device *ieee)
{
	if(IS_DOT11D_ENABLE(ieee) )
	{
		if(IS_COUNTRY_IE_VALID(ieee))
		{
			RESET_CIE_WATCHDOG(ieee);
		}
	}
	if (ieee->softmac_features & IEEE_SOFTMAC_SCAN){
		if (ieee->scanning == 0){
			ieee->scanning = 1;
			queue_delayed_work(ieee->wq, &ieee->softmac_scan_wq, 0);
		}
	}else
		ieee->start_scan(ieee->dev);

}