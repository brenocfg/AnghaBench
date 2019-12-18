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
struct tty_struct {int /*<<< orphan*/  name; struct esp_struct* driver_data; } ;
struct esp_struct {int timeout; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESI_GET_TX_AVAIL ; 
 int /*<<< orphan*/  ESI_NO_COMMAND ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_STAT1 ; 
 int /*<<< orphan*/  UART_ESI_STAT2 ; 
 int /*<<< orphan*/  current ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int serial_in (struct esp_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct esp_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void rs_wait_until_sent(struct tty_struct *tty, int timeout)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long orig_jiffies, char_time;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, "rs_wait_until_sent"))
		return;

	orig_jiffies = jiffies;
	char_time = ((info->timeout - HZ / 50) / 1024) / 5;

	if (!char_time)
		char_time = 1;

	spin_lock_irqsave(&info->lock, flags);
	serial_out(info, UART_ESI_CMD1, ESI_NO_COMMAND);
	serial_out(info, UART_ESI_CMD1, ESI_GET_TX_AVAIL);

	while ((serial_in(info, UART_ESI_STAT1) != 0x03) ||
		(serial_in(info, UART_ESI_STAT2) != 0xff)) {

		spin_unlock_irqrestore(&info->lock, flags);
		msleep_interruptible(jiffies_to_msecs(char_time));

		if (signal_pending(current))
			return;

		if (timeout && time_after(jiffies, orig_jiffies + timeout))
			return;

		spin_lock_irqsave(&info->lock, flags);
		serial_out(info, UART_ESI_CMD1, ESI_NO_COMMAND);
		serial_out(info, UART_ESI_CMD1, ESI_GET_TX_AVAIL);
	}
	spin_unlock_irqrestore(&info->lock, flags);
	set_current_state(TASK_RUNNING);
}