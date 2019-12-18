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
struct TYPE_4__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_2__ ap_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {scalar_t__ state; int /*<<< orphan*/  dev; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void notify_wx_assoc_event(struct ieee80211_device *ieee)
{
	union iwreq_data wrqu;
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	if (ieee->state == IEEE80211_LINKED)
		memcpy(wrqu.ap_addr.sa_data, ieee->current_network.bssid, ETH_ALEN);
	else
		memset(wrqu.ap_addr.sa_data, 0, ETH_ALEN);
	wireless_send_event(ieee->dev, SIOCGIWAP, &wrqu, NULL);
}