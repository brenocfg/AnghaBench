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
struct TYPE_4__ {scalar_t__ expires; } ;
struct r8180_priv {TYPE_2__ watch_dog_timer; TYPE_1__* ieee80211; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  GPIOChangeRFWorkItem; int /*<<< orphan*/  wq; int /*<<< orphan*/  hw_dig_wq; int /*<<< orphan*/  tx_pw_wq; } ;

/* Variables and functions */
 int CheckDig (struct net_device*) ; 
 scalar_t__ CheckHighPower (struct net_device*) ; 
 scalar_t__ CheckTxPwrTracking (struct net_device*) ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  IEEE80211_WATCH_DOG_TIME ; 
 scalar_t__ MSECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TxPwrTracking87SE (struct net_device*) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rtl8180_watch_dog (struct net_device*) ; 

void watch_dog_adaptive(unsigned long data)
{
	struct r8180_priv* priv = ieee80211_priv((struct net_device *)data);

	if (!priv->up) {
		DMESG("<----watch_dog_adaptive():driver is not up!\n");
		return;
	}

	// Tx High Power Mechanism.
#ifdef HIGH_POWER
	if(CheckHighPower((struct net_device *)data))
	{
		queue_work(priv->ieee80211->wq, (void *)&priv->ieee80211->tx_pw_wq);
	}
#endif

	// Tx Power Tracking on 87SE.
#ifdef TX_TRACK
	//if( priv->bTxPowerTrack )	//lzm mod 080826
	if( CheckTxPwrTracking((struct net_device *)data));
		TxPwrTracking87SE((struct net_device *)data);
#endif

	// Perform DIG immediately.
#ifdef SW_DIG
	if(CheckDig((struct net_device *)data) == true)
	{
		queue_work(priv->ieee80211->wq, (void *)&priv->ieee80211->hw_dig_wq);
	}
#endif
   	rtl8180_watch_dog((struct net_device *)data);

	queue_work(priv->ieee80211->wq, (void *)&priv->ieee80211->GPIOChangeRFWorkItem);

   	priv->watch_dog_timer.expires = jiffies + MSECS(IEEE80211_WATCH_DOG_TIME);
	add_timer(&priv->watch_dog_timer);
}