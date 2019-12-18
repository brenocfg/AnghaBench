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
struct esp_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  break_wait; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESI_ISSUE_BREAK ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ serial_paranoia_check (struct esp_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int esp_break(struct tty_struct *tty, int break_state)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, "esp_break"))
		return -EINVAL;

	if (break_state == -1) {
		spin_lock_irqsave(&info->lock, flags);
		serial_out(info, UART_ESI_CMD1, ESI_ISSUE_BREAK);
		serial_out(info, UART_ESI_CMD2, 0x01);
		spin_unlock_irqrestore(&info->lock, flags);

		/* FIXME - new style wait needed here */
		interruptible_sleep_on(&info->break_wait);
	} else {
		spin_lock_irqsave(&info->lock, flags);
		serial_out(info, UART_ESI_CMD1, ESI_ISSUE_BREAK);
		serial_out(info, UART_ESI_CMD2, 0x00);
		spin_unlock_irqrestore(&info->lock, flags);
	}
	return 0;
}