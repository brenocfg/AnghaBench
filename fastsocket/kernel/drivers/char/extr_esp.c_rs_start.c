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
struct esp_struct {int IER; int /*<<< orphan*/  lock; scalar_t__ xmit_buf; scalar_t__ xmit_cnt; } ;

/* Variables and functions */
 int ESI_SET_SRV_MASK ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ serial_paranoia_check (struct esp_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rs_start(struct tty_struct *tty)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, "rs_start"))
		return;

	spin_lock_irqsave(&info->lock, flags);
	if (info->xmit_cnt && info->xmit_buf && !(info->IER & UART_IER_THRI)) {
		info->IER |= UART_IER_THRI;
		serial_out(info, UART_ESI_CMD1, ESI_SET_SRV_MASK);
		serial_out(info, UART_ESI_CMD2, info->IER);
	}
	spin_unlock_irqrestore(&info->lock, flags);
}