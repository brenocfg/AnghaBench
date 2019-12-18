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
struct rt2x00_dev {scalar_t__ drv_data; int /*<<< orphan*/  autowake_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  pretbtt_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  txstatus_fifo; scalar_t__ workqueue; int /*<<< orphan*/  txdone_work; int /*<<< orphan*/  rxdone_work; int /*<<< orphan*/  txstatus_timer; int /*<<< orphan*/  sleep_work; int /*<<< orphan*/  autowakeup_work; int /*<<< orphan*/  intf_work; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00debug_deregister (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00leds_unregister (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_disable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_free_firmware (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_remove_hw (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_uninitialize (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_free (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void rt2x00lib_remove_dev(struct rt2x00_dev *rt2x00dev)
{
	clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);

	/*
	 * Disable radio.
	 */
	rt2x00lib_disable_radio(rt2x00dev);

	/*
	 * Stop all work.
	 */
	cancel_work_sync(&rt2x00dev->intf_work);
	cancel_delayed_work_sync(&rt2x00dev->autowakeup_work);
	cancel_work_sync(&rt2x00dev->sleep_work);
	if (rt2x00_is_usb(rt2x00dev)) {
		hrtimer_cancel(&rt2x00dev->txstatus_timer);
		cancel_work_sync(&rt2x00dev->rxdone_work);
		cancel_work_sync(&rt2x00dev->txdone_work);
	}
	if (rt2x00dev->workqueue)
		destroy_workqueue(rt2x00dev->workqueue);

	/*
	 * Free the tx status fifo.
	 */
	kfifo_free(&rt2x00dev->txstatus_fifo);

	/*
	 * Kill the tx status tasklet.
	 */
	tasklet_kill(&rt2x00dev->txstatus_tasklet);
	tasklet_kill(&rt2x00dev->pretbtt_tasklet);
	tasklet_kill(&rt2x00dev->tbtt_tasklet);
	tasklet_kill(&rt2x00dev->rxdone_tasklet);
	tasklet_kill(&rt2x00dev->autowake_tasklet);

	/*
	 * Uninitialize device.
	 */
	rt2x00lib_uninitialize(rt2x00dev);

	/*
	 * Free extra components
	 */
	rt2x00debug_deregister(rt2x00dev);
	rt2x00leds_unregister(rt2x00dev);

	/*
	 * Free ieee80211_hw memory.
	 */
	rt2x00lib_remove_hw(rt2x00dev);

	/*
	 * Free firmware image.
	 */
	rt2x00lib_free_firmware(rt2x00dev);

	/*
	 * Free queue structures.
	 */
	rt2x00queue_free(rt2x00dev);

	/*
	 * Free the driver data.
	 */
	if (rt2x00dev->drv_data)
		kfree(rt2x00dev->drv_data);
}