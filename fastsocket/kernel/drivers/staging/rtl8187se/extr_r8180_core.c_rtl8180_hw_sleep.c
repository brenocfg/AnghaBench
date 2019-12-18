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
typedef  scalar_t__ u32 ;
struct r8180_priv {int /*<<< orphan*/  ps_lock; TYPE_1__* ieee80211; int /*<<< orphan*/  DozePeriodInPast2Sec; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_sleep_wq; int /*<<< orphan*/  wq; int /*<<< orphan*/  hw_wakeup_wq; } ;

/* Variables and functions */
 int MAX_SLEEP_TIME ; 
 int MIN_SLEEP_TIME ; 
 scalar_t__ MSECS (int) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl8180_hw_sleep(struct net_device *dev, u32 th, u32 tl)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u32 rb = jiffies;
	unsigned long flags;

	spin_lock_irqsave(&priv->ps_lock,flags);

	/* Writing HW register with 0 equals to disable
	 * the timer, that is not really what we want
	 */
	tl -= MSECS(4+16+7);

	/* If the interval in witch we are requested to sleep is too
	 * short then give up and remain awake
	 */
	if(((tl>=rb)&& (tl-rb) <= MSECS(MIN_SLEEP_TIME))
		||((rb>tl)&& (rb-tl) < MSECS(MIN_SLEEP_TIME))) {
		spin_unlock_irqrestore(&priv->ps_lock,flags);
		printk("too short to sleep\n");
		return;
	}

	{
		u32 tmp = (tl>rb)?(tl-rb):(rb-tl);

		priv->DozePeriodInPast2Sec += jiffies_to_msecs(tmp);

		queue_delayed_work(priv->ieee80211->wq, &priv->ieee80211->hw_wakeup_wq, tmp); //as tl may be less than rb
	}
	/* if we suspect the TimerInt is gone beyond tl
	 * while setting it, then give up
	 */

	if(((tl > rb) && ((tl-rb) > MSECS(MAX_SLEEP_TIME)))||
		((tl < rb) && ((rb-tl) > MSECS(MAX_SLEEP_TIME)))) {
		spin_unlock_irqrestore(&priv->ps_lock,flags);
		return;
	}

	queue_work(priv->ieee80211->wq, (void *)&priv->ieee80211->hw_sleep_wq);
	spin_unlock_irqrestore(&priv->ps_lock,flags);
}