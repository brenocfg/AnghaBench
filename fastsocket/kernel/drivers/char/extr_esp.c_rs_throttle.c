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
struct esp_struct {int IER; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ESI_SET_RX_TIMEOUT ; 
 int ESI_SET_SRV_MASK ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int UART_IER_RDI ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ serial_paranoia_check (struct esp_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_chars_in_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_name (struct tty_struct*,char*) ; 

__attribute__((used)) static void rs_throttle(struct tty_struct *tty)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long flags;
#ifdef SERIAL_DEBUG_THROTTLE
	char	buf[64];

	printk("throttle %s: %d....\n", tty_name(tty, buf),
						tty_chars_in_buffer(tty));
#endif

	if (serial_paranoia_check(info, tty->name, "rs_throttle"))
		return;

	spin_lock_irqsave(&info->lock, flags);
	info->IER &= ~UART_IER_RDI;
	serial_out(info, UART_ESI_CMD1, ESI_SET_SRV_MASK);
	serial_out(info, UART_ESI_CMD2, info->IER);
	serial_out(info, UART_ESI_CMD1, ESI_SET_RX_TIMEOUT);
	serial_out(info, UART_ESI_CMD2, 0x00);
	spin_unlock_irqrestore(&info->lock, flags);
}