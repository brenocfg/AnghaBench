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
struct TYPE_2__ {scalar_t__ expires; } ;
struct srmcons_private {int /*<<< orphan*/  lock; TYPE_1__ timer; scalar_t__ tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srmcons_callback_lock ; 
 int /*<<< orphan*/  srmcons_do_receive_chars (scalar_t__) ; 

__attribute__((used)) static void
srmcons_receive_chars(unsigned long data)
{
	struct srmcons_private *srmconsp = (struct srmcons_private *)data;
	unsigned long flags;
	int incr = 10;

	local_irq_save(flags);
	if (spin_trylock(&srmcons_callback_lock)) {
		if (!srmcons_do_receive_chars(srmconsp->tty))
			incr = 100;
		spin_unlock(&srmcons_callback_lock);
	} 

	spin_lock(&srmconsp->lock);
	if (srmconsp->tty) {
		srmconsp->timer.expires = jiffies + incr;
		add_timer(&srmconsp->timer);
	}
	spin_unlock(&srmconsp->lock);

	local_irq_restore(flags);
}