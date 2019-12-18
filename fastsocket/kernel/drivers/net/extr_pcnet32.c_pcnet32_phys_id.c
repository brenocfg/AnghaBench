#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct TYPE_4__ {unsigned long data; void* function; } ;
struct pcnet32_access {int (* read_bcr ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* write_bcr ) (int /*<<< orphan*/ ,int,int) ;} ;
struct pcnet32_private {int /*<<< orphan*/  lock; TYPE_1__ blink_timer; struct pcnet32_access a; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int HZ ; 
 int MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 scalar_t__ pcnet32_led_blink_callback ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pcnet32_phys_id(struct net_device *dev, u32 data)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	struct pcnet32_access *a = &lp->a;
	ulong ioaddr = dev->base_addr;
	unsigned long flags;
	int i, regs[4];

	if (!lp->blink_timer.function) {
		init_timer(&lp->blink_timer);
		lp->blink_timer.function = (void *)pcnet32_led_blink_callback;
		lp->blink_timer.data = (unsigned long)dev;
	}

	/* Save the current value of the bcrs */
	spin_lock_irqsave(&lp->lock, flags);
	for (i = 4; i < 8; i++) {
		regs[i - 4] = a->read_bcr(ioaddr, i);
	}
	spin_unlock_irqrestore(&lp->lock, flags);

	mod_timer(&lp->blink_timer, jiffies);
	set_current_state(TASK_INTERRUPTIBLE);

	/* AV: the limit here makes no sense whatsoever */
	if ((!data) || (data > (u32) (MAX_SCHEDULE_TIMEOUT / HZ)))
		data = (u32) (MAX_SCHEDULE_TIMEOUT / HZ);

	msleep_interruptible(data * 1000);
	del_timer_sync(&lp->blink_timer);

	/* Restore the original value of the bcrs */
	spin_lock_irqsave(&lp->lock, flags);
	for (i = 4; i < 8; i++) {
		a->write_bcr(ioaddr, i, regs[i - 4]);
	}
	spin_unlock_irqrestore(&lp->lock, flags);

	return 0;
}