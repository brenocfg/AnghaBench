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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int eth_mac_addr (struct net_device*,struct sockaddr*) ; 
 scalar_t__ ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 int ieee80211_verify_mac (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_change_mac(struct net_device *dev, void *addr)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct sockaddr *sa = addr;
	int ret;

	if (ieee80211_sdata_running(sdata))
		return -EBUSY;

	ret = ieee80211_verify_mac(sdata, sa->sa_data);
	if (ret)
		return ret;

	ret = eth_mac_addr(dev, sa);

	if (ret == 0)
		memcpy(sdata->vif.addr, sa->sa_data, ETH_ALEN);

	return ret;
}