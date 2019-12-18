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
struct zd_usb_rx {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  reset_timer_tasklet; int /*<<< orphan*/  setup_mutex; } ;
struct zd_usb {struct zd_usb_rx rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __zd_usb_disable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void zd_usb_disable_rx(struct zd_usb *usb)
{
	struct zd_usb_rx *rx = &usb->rx;

	mutex_lock(&rx->setup_mutex);
	__zd_usb_disable_rx(usb);
	mutex_unlock(&rx->setup_mutex);

	tasklet_kill(&rx->reset_timer_tasklet);
	cancel_delayed_work_sync(&rx->idle_work);
}