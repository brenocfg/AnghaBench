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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  txstatus_timer; int /*<<< orphan*/  txdone_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  txstatus_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  TX_STATUS_READING ; 
 int /*<<< orphan*/  TX_STA_FIFO_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rt2800usb_txstatus_pending (struct rt2x00_dev*) ; 
 scalar_t__ rt2800usb_txstatus_timeout (struct rt2x00_dev*) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*,...) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rt2800usb_tx_sta_fifo_read_completed(struct rt2x00_dev *rt2x00dev,
						 int urb_status, u32 tx_status)
{
	bool valid;

	if (urb_status) {
		rt2x00_warn(rt2x00dev, "TX status read failed %d\n",
			    urb_status);

		goto stop_reading;
	}

	valid = rt2x00_get_field32(tx_status, TX_STA_FIFO_VALID);
	if (valid) {
		if (!kfifo_put(&rt2x00dev->txstatus_fifo, &tx_status))
			rt2x00_warn(rt2x00dev, "TX status FIFO overrun\n");

		queue_work(rt2x00dev->workqueue, &rt2x00dev->txdone_work);

		/* Reschedule urb to read TX status again instantly */
		return true;
	}

	/* Check if there is any entry that timedout waiting on TX status */
	if (rt2800usb_txstatus_timeout(rt2x00dev))
		queue_work(rt2x00dev->workqueue, &rt2x00dev->txdone_work);

	if (rt2800usb_txstatus_pending(rt2x00dev)) {
		/* Read register after 250 us */
		hrtimer_start(&rt2x00dev->txstatus_timer, ktime_set(0, 250000),
			      HRTIMER_MODE_REL);
		return false;
	}

stop_reading:
	clear_bit(TX_STATUS_READING, &rt2x00dev->flags);
	/*
	 * There is small race window above, between txstatus pending check and
	 * clear_bit someone could do rt2x00usb_interrupt_txdone, so recheck
	 * here again if status reading is needed.
	 */
	if (rt2800usb_txstatus_pending(rt2x00dev) &&
	    !test_and_set_bit(TX_STATUS_READING, &rt2x00dev->flags))
		return true;
	else
		return false;
}