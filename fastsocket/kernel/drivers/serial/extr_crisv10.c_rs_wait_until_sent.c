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
struct tty_struct {scalar_t__ driver_data; } ;
struct TYPE_2__ {scalar_t__ head; scalar_t__ tail; } ;
struct e100_serial {unsigned long last_tx_active; unsigned long last_tx_active_usec; int* ostatusadr; int char_time_usec; TYPE_1__ xmit; } ;

/* Variables and functions */
 unsigned long GET_JIFFIES_USEC () ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  current ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void rs_wait_until_sent(struct tty_struct *tty, int timeout)
{
	unsigned long orig_jiffies;
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	unsigned long curr_time = jiffies;
	unsigned long curr_time_usec = GET_JIFFIES_USEC();
	long elapsed_usec =
		(curr_time - info->last_tx_active) * (1000000/HZ) +
		curr_time_usec - info->last_tx_active_usec;

	/*
	 * Check R_DMA_CHx_STATUS bit 0-6=number of available bytes in FIFO
	 * R_DMA_CHx_HWSW bit 31-16=nbr of bytes left in DMA buffer (0=64k)
	 */
	lock_kernel();
	orig_jiffies = jiffies;
	while (info->xmit.head != info->xmit.tail || /* More in send queue */
	       (*info->ostatusadr & 0x007f) ||  /* more in FIFO */
	       (elapsed_usec < 2*info->char_time_usec)) {
		schedule_timeout_interruptible(1);
		if (signal_pending(current))
			break;
		if (timeout && time_after(jiffies, orig_jiffies + timeout))
			break;
		curr_time = jiffies;
		curr_time_usec = GET_JIFFIES_USEC();
		elapsed_usec =
			(curr_time - info->last_tx_active) * (1000000/HZ) +
			curr_time_usec - info->last_tx_active_usec;
	}
	set_current_state(TASK_RUNNING);
	unlock_kernel();
}