#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int maxkeyup; } ;
struct scc_channel {int /*<<< orphan*/  lock; TYPE_2__ tx_wdog; TYPE_1__ kiss; } ;

/* Variables and functions */
 int HZ ; 
 int TIMER_OFF ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  t_maxkeyup ; 

__attribute__((used)) static void scc_start_maxkeyup(struct scc_channel *scc)
{
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	del_timer(&scc->tx_wdog);
	
	if (scc->kiss.maxkeyup != 0 && scc->kiss.maxkeyup != TIMER_OFF)
	{
		scc->tx_wdog.data = (unsigned long) scc;
		scc->tx_wdog.function = t_maxkeyup;
		scc->tx_wdog.expires = jiffies + HZ*scc->kiss.maxkeyup;
		add_timer(&scc->tx_wdog);
	}
	spin_unlock_irqrestore(&scc->lock, flags);
}