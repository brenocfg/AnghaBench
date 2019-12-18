#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_5__ {struct tty_struct* tty; } ;
struct m68k_serial {size_t line; scalar_t__ is_cons; TYPE_1__ port; } ;
struct TYPE_6__ {unsigned short w; } ;
struct TYPE_7__ {TYPE_2__ urx; } ;
typedef  TYPE_3__ m68328_uart ;

/* Variables and functions */
 unsigned char GET_FIELD (unsigned short,int /*<<< orphan*/ ) ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 unsigned short URX_BREAK ; 
 unsigned short URX_DATA_READY ; 
 unsigned short URX_FRAME_ERROR ; 
 unsigned short URX_OVRUN ; 
 unsigned short URX_PARITY_ERROR ; 
 int /*<<< orphan*/  URX_RXDATA ; 
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  keypress_wait ; 
 int /*<<< orphan*/  show_buffers () ; 
 int /*<<< orphan*/  show_free_areas () ; 
 int /*<<< orphan*/  show_state () ; 
 int /*<<< orphan*/  status_handle (struct m68k_serial*,unsigned short) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_struct*) ; 
 TYPE_3__* uart_addr ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void receive_chars(struct m68k_serial *info, unsigned short rx)
{
	struct tty_struct *tty = info->port.tty;
	m68328_uart *uart = &uart_addr[info->line];
	unsigned char ch, flag;

	/*
	 * This do { } while() loop will get ALL chars out of Rx FIFO 
         */
#ifndef CONFIG_XCOPILOT_BUGS
	do {
#endif	
		ch = GET_FIELD(rx, URX_RXDATA);
	
		if(info->is_cons) {
			if(URX_BREAK & rx) { /* whee, break received */
				status_handle(info, rx);
				return;
#ifdef CONFIG_MAGIC_SYSRQ
			} else if (ch == 0x10) { /* ^P */
				show_state();
				show_free_areas();
				show_buffers();
/*				show_net_buffers(); */
				return;
			} else if (ch == 0x12) { /* ^R */
				emergency_restart();
				return;
#endif /* CONFIG_MAGIC_SYSRQ */
			}
			/* It is a 'keyboard interrupt' ;-) */
#ifdef CONFIG_CONSOLE
			wake_up(&keypress_wait);
#endif			
		}

		if(!tty)
			goto clear_and_exit;
		
		flag = TTY_NORMAL;

		if(rx & URX_PARITY_ERROR) {
			flag = TTY_PARITY;
			status_handle(info, rx);
		} else if(rx & URX_OVRUN) {
			flag = TTY_OVERRUN;
			status_handle(info, rx);
		} else if(rx & URX_FRAME_ERROR) {
			flag = TTY_FRAME;
			status_handle(info, rx);
		}
		tty_insert_flip_char(tty, ch, flag);
#ifndef CONFIG_XCOPILOT_BUGS
	} while((rx = uart->urx.w) & URX_DATA_READY);
#endif

	tty_schedule_flip(tty);

clear_and_exit:
	return;
}