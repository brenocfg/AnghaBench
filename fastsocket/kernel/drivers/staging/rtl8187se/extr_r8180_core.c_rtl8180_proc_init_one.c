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
struct r8180_priv {int /*<<< orphan*/  dir_dev; } ;
struct proc_dir_entry {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*,int /*<<< orphan*/ ) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 struct proc_dir_entry* create_proc_read_entry (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  proc_get_registers ; 
 int /*<<< orphan*/  proc_get_stats_hw ; 
 int /*<<< orphan*/  proc_get_stats_rx ; 
 int /*<<< orphan*/  proc_get_stats_tx ; 
 int /*<<< orphan*/  rtl8180_proc ; 

void rtl8180_proc_init_one(struct net_device *dev)
{
	struct proc_dir_entry *e;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	priv->dir_dev = rtl8180_proc;
	if (!priv->dir_dev) {
		DMESGE("Unable to initialize /proc/net/r8180/%s\n",
		      dev->name);
		return;
	}

	e = create_proc_read_entry("stats-hw", S_IFREG | S_IRUGO,
				   priv->dir_dev, proc_get_stats_hw, dev);
	if (!e) {
		DMESGE("Unable to initialize "
		      "/proc/net/r8180/%s/stats-hw\n",
		      dev->name);
	}

	e = create_proc_read_entry("stats-rx", S_IFREG | S_IRUGO,
				   priv->dir_dev, proc_get_stats_rx, dev);
	if (!e) {
		DMESGE("Unable to initialize "
		      "/proc/net/r8180/%s/stats-rx\n",
		      dev->name);
	}


	e = create_proc_read_entry("stats-tx", S_IFREG | S_IRUGO,
				   priv->dir_dev, proc_get_stats_tx, dev);
	if (!e) {
		DMESGE("Unable to initialize "
		      "/proc/net/r8180/%s/stats-tx\n",
		      dev->name);
	}

	e = create_proc_read_entry("registers", S_IFREG | S_IRUGO,
				   priv->dir_dev, proc_get_registers, dev);
	if (!e) {
		DMESGE("Unable to initialize "
		      "/proc/net/r8180/%s/registers\n",
		      dev->name);
	}
}