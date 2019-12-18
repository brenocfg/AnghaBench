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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  wdev; TYPE_1__ vif; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int ieee80211_check_concurrent_iface (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_do_open (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_open(struct net_device *dev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	int err;

	/* fail early if user set an invalid address */
	if (!is_valid_ether_addr(dev->dev_addr))
		return -EADDRNOTAVAIL;

	err = ieee80211_check_concurrent_iface(sdata, sdata->vif.type);
	if (err)
		return err;

	return ieee80211_do_open(&sdata->wdev, true);
}