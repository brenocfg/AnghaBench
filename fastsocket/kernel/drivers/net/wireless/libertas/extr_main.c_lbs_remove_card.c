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
struct TYPE_2__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct net_device {int dummy; } ;
struct lbs_private {scalar_t__ psmode; int surpriseremoved; struct net_device* dev; int /*<<< orphan*/  main_thread; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  assoc_work; int /*<<< orphan*/  scan_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  CMD_OPTION_WAITFORRSP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ LBS802_11POWERMODECAM ; 
 scalar_t__ LBS802_11POWERMODEMAX_PSP ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_main (char*) ; 
 int /*<<< orphan*/  lbs_free_adapter (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_ps_wakeup (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_remove_mesh (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_remove_rtap (struct lbs_private*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void lbs_remove_card(struct lbs_private *priv)
{
	struct net_device *dev = priv->dev;
	union iwreq_data wrqu;

	lbs_deb_enter(LBS_DEB_MAIN);

	lbs_remove_mesh(priv);
	lbs_remove_rtap(priv);

	dev = priv->dev;

	cancel_delayed_work_sync(&priv->scan_work);
	cancel_delayed_work_sync(&priv->assoc_work);
	cancel_work_sync(&priv->mcast_work);

	/* worker thread destruction blocks on the in-flight command which
	 * should have been cleared already in lbs_stop_card().
	 */
	lbs_deb_main("destroying worker thread\n");
	destroy_workqueue(priv->work_thread);
	lbs_deb_main("done destroying worker thread\n");

	if (priv->psmode == LBS802_11POWERMODEMAX_PSP) {
		priv->psmode = LBS802_11POWERMODECAM;
		lbs_ps_wakeup(priv, CMD_OPTION_WAITFORRSP);
	}

	memset(wrqu.ap_addr.sa_data, 0xaa, ETH_ALEN);
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, NULL);

	/* Stop the thread servicing the interrupts */
	priv->surpriseremoved = 1;
	kthread_stop(priv->main_thread);

	lbs_free_adapter(priv);

	priv->dev = NULL;
	free_netdev(dev);

	lbs_deb_leave(LBS_DEB_MAIN);
}