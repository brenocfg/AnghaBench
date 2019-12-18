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
struct net_device {int dummy; } ;
struct ieee80211_device {struct ieee80211_crypt_data** crypt; int /*<<< orphan*/  crypt_deinit_timer; struct ieee80211_crypt_data* pHTInfo; } ;
struct ieee80211_crypt_data {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveAllTS (struct ieee80211_device*) ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_crypt_deinit_entries (struct ieee80211_device*,int) ; 
 int /*<<< orphan*/  ieee80211_networks_free (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_free (struct ieee80211_device*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_crypt_data*) ; 
 struct ieee80211_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void free_ieee80211(struct net_device *dev)
{
	struct ieee80211_device *ieee = netdev_priv(dev);
	int i;
	//struct list_head *p, *q;
//	del_timer_sync(&ieee->SwBwTimer);
#if 1
	if (ieee->pHTInfo != NULL)
	{
		kfree(ieee->pHTInfo);
		ieee->pHTInfo = NULL;
	}
#endif
	RemoveAllTS(ieee);
	ieee80211_softmac_free(ieee);
	del_timer_sync(&ieee->crypt_deinit_timer);
	ieee80211_crypt_deinit_entries(ieee, 1);

	for (i = 0; i < WEP_KEYS; i++) {
		struct ieee80211_crypt_data *crypt = ieee->crypt[i];
		if (crypt) {
			if (crypt->ops)
				crypt->ops->deinit(crypt->priv);
			kfree(crypt);
			ieee->crypt[i] = NULL;
		}
	}

	ieee80211_networks_free(ieee);
	free_netdev(dev);
}