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
struct zilog_channel {int /*<<< orphan*/  control; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_ip22zilog_port {struct uart_ip22zilog_port* next; TYPE_1__ port; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned char CHAEXT ; 
 unsigned char CHARxIP ; 
 unsigned char CHATxIP ; 
 unsigned char CHBEXT ; 
 unsigned char CHBRxIP ; 
 unsigned char CHBTxIP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 struct tty_struct* ip22zilog_receive_chars (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 int /*<<< orphan*/  ip22zilog_status_handle (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 int /*<<< orphan*/  ip22zilog_transmit_chars (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 unsigned char read_zsreg (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ip22zilog_interrupt(int irq, void *dev_id)
{
	struct uart_ip22zilog_port *up = dev_id;

	while (up) {
		struct zilog_channel *channel
			= ZILOG_CHANNEL_FROM_PORT(&up->port);
		struct tty_struct *tty;
		unsigned char r3;

		spin_lock(&up->port.lock);
		r3 = read_zsreg(channel, R3);

		/* Channel A */
		tty = NULL;
		if (r3 & (CHAEXT | CHATxIP | CHARxIP)) {
			writeb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			if (r3 & CHARxIP)
				tty = ip22zilog_receive_chars(up, channel);
			if (r3 & CHAEXT)
				ip22zilog_status_handle(up, channel);
			if (r3 & CHATxIP)
				ip22zilog_transmit_chars(up, channel);
		}
		spin_unlock(&up->port.lock);

		if (tty)
			tty_flip_buffer_push(tty);

		/* Channel B */
		up = up->next;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);

		spin_lock(&up->port.lock);
		tty = NULL;
		if (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) {
			writeb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			if (r3 & CHBRxIP)
				tty = ip22zilog_receive_chars(up, channel);
			if (r3 & CHBEXT)
				ip22zilog_status_handle(up, channel);
			if (r3 & CHBTxIP)
				ip22zilog_transmit_chars(up, channel);
		}
		spin_unlock(&up->port.lock);

		if (tty)
			tty_flip_buffer_push(tty);

		up = up->next;
	}

	return IRQ_HANDLED;
}