#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* tty; } ;
struct m68k_serial {size_t line; scalar_t__ xmit_cnt; int xmit_tail; int /*<<< orphan*/  tqueue; scalar_t__* xmit_buf; TYPE_2__ port; scalar_t__ x_char; } ;
struct TYPE_9__ {scalar_t__ txdata; } ;
struct TYPE_10__ {TYPE_3__ b; } ;
struct TYPE_11__ {int /*<<< orphan*/  ustcnt; TYPE_4__ utx; } ;
typedef  TYPE_5__ m68328_uart ;
struct TYPE_7__ {scalar_t__ stopped; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  USTCNT_TX_INTR_MASK ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_5__* uart_addr ; 

__attribute__((used)) static void transmit_chars(struct m68k_serial *info)
{
	m68328_uart *uart = &uart_addr[info->line];

	if (info->x_char) {
		/* Send next char */
		uart->utx.b.txdata = info->x_char;
		info->x_char = 0;
		goto clear_and_return;
	}

	if((info->xmit_cnt <= 0) || info->port.tty->stopped) {
		/* That's peculiar... TX ints off */
		uart->ustcnt &= ~USTCNT_TX_INTR_MASK;
		goto clear_and_return;
	}

	/* Send char */
	uart->utx.b.txdata = info->xmit_buf[info->xmit_tail++];
	info->xmit_tail = info->xmit_tail & (SERIAL_XMIT_SIZE-1);
	info->xmit_cnt--;

	if (info->xmit_cnt < WAKEUP_CHARS)
		schedule_work(&info->tqueue);

	if(info->xmit_cnt <= 0) {
		/* All done for now... TX ints off */
		uart->ustcnt &= ~USTCNT_TX_INTR_MASK;
		goto clear_and_return;
	}

clear_and_return:
	/* Clear interrupt (should be auto)*/
	return;
}