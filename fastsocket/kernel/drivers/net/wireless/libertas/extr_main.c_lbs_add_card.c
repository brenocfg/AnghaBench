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
struct net_device {int watchdog_timeo; int flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; struct lbs_private* ml_priv; } ;
struct lbs_private {int mesh_ssid_len; int wol_criteria; int wol_gpio; int /*<<< orphan*/  mesh_ssid; int /*<<< orphan*/  sync_channel; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  assoc_work; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  main_thread; int /*<<< orphan*/  waitq; int /*<<< orphan*/ * rtap_net_dev; scalar_t__ infra_open; scalar_t__ mesh_open; void* card; struct net_device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  lbs_association_worker ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_thread (char*) ; 
 int /*<<< orphan*/  lbs_ethtool_ops ; 
 int /*<<< orphan*/  lbs_free_adapter (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_handler_def ; 
 scalar_t__ lbs_init_adapter (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_netdev_ops ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  lbs_scan_worker ; 
 int /*<<< orphan*/  lbs_set_mcast_worker ; 
 int /*<<< orphan*/  lbs_sync_channel_worker ; 
 int /*<<< orphan*/  lbs_thread ; 
 struct lbs_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

struct lbs_private *lbs_add_card(void *card, struct device *dmdev)
{
	struct net_device *dev = NULL;
	struct lbs_private *priv = NULL;

	lbs_deb_enter(LBS_DEB_MAIN);

	/* Allocate an Ethernet device and register it */
	dev = alloc_etherdev(sizeof(struct lbs_private));
	if (!dev) {
		lbs_pr_err("init wlanX device failed\n");
		goto done;
	}
	priv = netdev_priv(dev);
	dev->ml_priv = priv;

	if (lbs_init_adapter(priv)) {
		lbs_pr_err("failed to initialize adapter structure.\n");
		goto err_init_adapter;
	}

	priv->dev = dev;
	priv->card = card;
	priv->mesh_open = 0;
	priv->infra_open = 0;

	/* Setup the OS Interface to our functions */
 	dev->netdev_ops = &lbs_netdev_ops;
	dev->watchdog_timeo = 5 * HZ;
	dev->ethtool_ops = &lbs_ethtool_ops;
#ifdef	WIRELESS_EXT
	dev->wireless_handlers = &lbs_handler_def;
#endif
	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;

	SET_NETDEV_DEV(dev, dmdev);

	priv->rtap_net_dev = NULL;
	strcpy(dev->name, "wlan%d");

	lbs_deb_thread("Starting main thread...\n");
	init_waitqueue_head(&priv->waitq);
	priv->main_thread = kthread_run(lbs_thread, dev, "lbs_main");
	if (IS_ERR(priv->main_thread)) {
		lbs_deb_thread("Error creating main thread.\n");
		goto err_init_adapter;
	}

	priv->work_thread = create_singlethread_workqueue("lbs_worker");
	INIT_DELAYED_WORK(&priv->assoc_work, lbs_association_worker);
	INIT_DELAYED_WORK(&priv->scan_work, lbs_scan_worker);
	INIT_WORK(&priv->mcast_work, lbs_set_mcast_worker);
	INIT_WORK(&priv->sync_channel, lbs_sync_channel_worker);

	sprintf(priv->mesh_ssid, "mesh");
	priv->mesh_ssid_len = 4;

	priv->wol_criteria = 0xffffffff;
	priv->wol_gpio = 0xff;

	goto done;

err_init_adapter:
	lbs_free_adapter(priv);
	free_netdev(dev);
	priv = NULL;

done:
	lbs_deb_leave_args(LBS_DEB_MAIN, "priv %p", priv);
	return priv;
}