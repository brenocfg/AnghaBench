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
struct r8192_priv {int /*<<< orphan*/ * dir_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtl8192_proc ; 

void rtl8192_proc_remove_one(struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);


	if (priv->dir_dev) {
	//	remove_proc_entry("stats-hw", priv->dir_dev);
		remove_proc_entry("stats-tx", priv->dir_dev);
		remove_proc_entry("stats-rx", priv->dir_dev);
	//	remove_proc_entry("stats-ieee", priv->dir_dev);
		remove_proc_entry("stats-ap", priv->dir_dev);
		remove_proc_entry("registers", priv->dir_dev);
		remove_proc_entry("registers-1", priv->dir_dev);
		remove_proc_entry("registers-2", priv->dir_dev);
		remove_proc_entry("registers-8", priv->dir_dev);
		remove_proc_entry("registers-9", priv->dir_dev);
		remove_proc_entry("registers-a", priv->dir_dev);
		remove_proc_entry("registers-b", priv->dir_dev);
		remove_proc_entry("registers-c", priv->dir_dev);
		remove_proc_entry("registers-d", priv->dir_dev);
		remove_proc_entry("registers-e", priv->dir_dev);
	//	remove_proc_entry("cck-registers",priv->dir_dev);
	//	remove_proc_entry("ofdm-registers",priv->dir_dev);
		//remove_proc_entry(dev->name, rtl8192_proc);
		remove_proc_entry("wlan0", rtl8192_proc);
		priv->dir_dev = NULL;
	}
}