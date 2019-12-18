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
struct r8192_priv {int /*<<< orphan*/  irq_rx_tasklet; TYPE_1__* ieee80211; int /*<<< orphan*/  qos_activate; int /*<<< orphan*/  initialgain_operate_wq; int /*<<< orphan*/  update_beacon_wq; int /*<<< orphan*/  rfpath_check_wq; int /*<<< orphan*/  txpower_tracking_wq; int /*<<< orphan*/  watch_dog_wq; int /*<<< orphan*/  reset_wq; void* priv_wq; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_sleep_wq; int /*<<< orphan*/  hw_wakeup_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* InitialGainOperateWorkItemCallBack ; 
 void* create_workqueue (int /*<<< orphan*/ ,...) ; 
 void* dm_rf_pathcheck_workitemcallback ; 
 void* dm_txpower_trackingcallback ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ rtl8192_hw_sleep_wq ; 
 scalar_t__ rtl8192_hw_wakeup_wq ; 
 scalar_t__ rtl8192_irq_rx_tasklet ; 
 int /*<<< orphan*/  rtl8192_qos_activate ; 
 int /*<<< orphan*/  rtl8192_restart ; 
 void* rtl8192_update_beacon ; 
 void* rtl819x_watchdog_wqcallback ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static void rtl8192_init_priv_task(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

#ifdef PF_SYNCTHREAD
	priv->priv_wq = create_workqueue(DRV_NAME,0);
#else
	priv->priv_wq = create_workqueue(DRV_NAME);
#endif

	INIT_WORK(&priv->reset_wq, rtl8192_restart);

	//INIT_DELAYED_WORK(&priv->watch_dog_wq, hal_dm_watchdog);
	INIT_DELAYED_WORK(&priv->watch_dog_wq, rtl819x_watchdog_wqcallback);
	INIT_DELAYED_WORK(&priv->txpower_tracking_wq,  dm_txpower_trackingcallback);
//	INIT_DELAYED_WORK(&priv->gpio_change_rf_wq,  dm_gpio_change_rf_callback);
	INIT_DELAYED_WORK(&priv->rfpath_check_wq,  dm_rf_pathcheck_workitemcallback);
	INIT_DELAYED_WORK(&priv->update_beacon_wq, rtl8192_update_beacon);
	INIT_DELAYED_WORK(&priv->initialgain_operate_wq, InitialGainOperateWorkItemCallBack);
	//INIT_WORK(&priv->SwChnlWorkItem,  rtl8192_SwChnl_WorkItem);
	//INIT_WORK(&priv->SetBWModeWorkItem,  rtl8192_SetBWModeWorkItem);
	INIT_WORK(&priv->qos_activate, rtl8192_qos_activate);
	INIT_DELAYED_WORK(&priv->ieee80211->hw_wakeup_wq,(void*) rtl8192_hw_wakeup_wq);
	INIT_DELAYED_WORK(&priv->ieee80211->hw_sleep_wq,(void*) rtl8192_hw_sleep_wq);

	tasklet_init(&priv->irq_rx_tasklet,
	     (void(*)(unsigned long))rtl8192_irq_rx_tasklet,
	     (unsigned long)priv);
}