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
struct r8192_priv {int /*<<< orphan*/  gpio_change_rf_wq; int /*<<< orphan*/  priv_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_check_rfctrl_gpio(struct net_device * dev)
{
#ifdef RTL8192E
	struct r8192_priv *priv = ieee80211_priv(dev);
#endif

	// Walk around for DTM test, we will not enable HW - radio on/off because r/w
	// page 1 register before Lextra bus is enabled cause system fails when resuming
	// from S4. 20080218, Emily

	// Stop to execute workitem to prevent S3/S4 bug.
#ifdef RTL8190P
	return;
#endif
#ifdef RTL8192U
	return;
#endif
#ifdef RTL8192E
		queue_delayed_work(priv->priv_wq,&priv->gpio_change_rf_wq,0);
#endif

}