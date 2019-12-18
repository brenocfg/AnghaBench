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
struct b43_wldev {TYPE_1__* wl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  b43_do_interrupt_thread (struct b43_wldev*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t b43_interrupt_thread_handler(int irq, void *dev_id)
{
	struct b43_wldev *dev = dev_id;

	mutex_lock(&dev->wl->mutex);
	b43_do_interrupt_thread(dev);
	mmiowb();
	mutex_unlock(&dev->wl->mutex);

	return IRQ_HANDLED;
}