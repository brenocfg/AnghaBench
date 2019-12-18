#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {TYPE_3__* state; } ;
struct ktermios {int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;
struct jsm_channel {struct jsm_board* ch_bd; int /*<<< orphan*/  ch_open_count; int /*<<< orphan*/  ch_stopc; int /*<<< orphan*/  ch_startc; int /*<<< orphan*/  ch_c_lflag; int /*<<< orphan*/  ch_c_oflag; int /*<<< orphan*/  ch_c_iflag; int /*<<< orphan*/  ch_c_cflag; scalar_t__ ch_stops_sent; scalar_t__ ch_cached_lsr; int /*<<< orphan*/  ch_flags; scalar_t__ ch_w_tail; scalar_t__ ch_w_head; scalar_t__ ch_e_tail; scalar_t__ ch_e_head; scalar_t__ ch_r_tail; scalar_t__ ch_r_head; void* ch_wqueue; void* ch_equeue; void* ch_rqueue; } ;
struct jsm_board {int /*<<< orphan*/  pci_dev; TYPE_4__* bd_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* param ) (struct jsm_channel*) ;int /*<<< orphan*/  (* uart_init ) (struct jsm_channel*) ;int /*<<< orphan*/  (* flush_uart_read ) (struct jsm_channel*) ;int /*<<< orphan*/  (* flush_uart_write ) (struct jsm_channel*) ;} ;
struct TYPE_6__ {TYPE_1__* tty; } ;
struct TYPE_7__ {TYPE_2__ port; } ;
struct TYPE_5__ {struct ktermios* termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_OPENING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EQUEUESIZE ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  OPEN ; 
 int /*<<< orphan*/  RQUEUESIZE ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  WQUEUESIZE ; 
 int /*<<< orphan*/  jsm_carrier (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub2 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub3 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub4 (struct jsm_channel*) ; 

__attribute__((used)) static int jsm_tty_open(struct uart_port *port)
{
	struct jsm_board *brd;
	struct jsm_channel *channel = (struct jsm_channel *)port;
	struct ktermios *termios;

	/* Get board pointer from our array of majors we have allocated */
	brd = channel->ch_bd;

	/*
	 * Allocate channel buffers for read/write/error.
	 * Set flag, so we don't get trounced on.
	 */
	channel->ch_flags |= (CH_OPENING);

	/* Drop locks, as malloc with GFP_KERNEL can sleep */

	if (!channel->ch_rqueue) {
		channel->ch_rqueue = kzalloc(RQUEUESIZE, GFP_KERNEL);
		if (!channel->ch_rqueue) {
			jsm_printk(INIT, ERR, &channel->ch_bd->pci_dev,
				"unable to allocate read queue buf");
			return -ENOMEM;
		}
	}
	if (!channel->ch_equeue) {
		channel->ch_equeue = kzalloc(EQUEUESIZE, GFP_KERNEL);
		if (!channel->ch_equeue) {
			jsm_printk(INIT, ERR, &channel->ch_bd->pci_dev,
				"unable to allocate error queue buf");
			return -ENOMEM;
		}
	}
	if (!channel->ch_wqueue) {
		channel->ch_wqueue = kzalloc(WQUEUESIZE, GFP_KERNEL);
		if (!channel->ch_wqueue) {
			jsm_printk(INIT, ERR, &channel->ch_bd->pci_dev,
				"unable to allocate write queue buf");
			return -ENOMEM;
		}
	}

	channel->ch_flags &= ~(CH_OPENING);
	/*
	 * Initialize if neither terminal is open.
	 */
	jsm_printk(OPEN, INFO, &channel->ch_bd->pci_dev,
		"jsm_open: initializing channel in open...\n");

	/*
	 * Flush input queues.
	 */
	channel->ch_r_head = channel->ch_r_tail = 0;
	channel->ch_e_head = channel->ch_e_tail = 0;
	channel->ch_w_head = channel->ch_w_tail = 0;

	brd->bd_ops->flush_uart_write(channel);
	brd->bd_ops->flush_uart_read(channel);

	channel->ch_flags = 0;
	channel->ch_cached_lsr = 0;
	channel->ch_stops_sent = 0;

	termios = port->state->port.tty->termios;
	channel->ch_c_cflag	= termios->c_cflag;
	channel->ch_c_iflag	= termios->c_iflag;
	channel->ch_c_oflag	= termios->c_oflag;
	channel->ch_c_lflag	= termios->c_lflag;
	channel->ch_startc	= termios->c_cc[VSTART];
	channel->ch_stopc	= termios->c_cc[VSTOP];

	/* Tell UART to init itself */
	brd->bd_ops->uart_init(channel);

	/*
	 * Run param in case we changed anything
	 */
	brd->bd_ops->param(channel);

	jsm_carrier(channel);

	channel->ch_open_count++;

	jsm_printk(OPEN, INFO, &channel->ch_bd->pci_dev, "finish\n");
	return 0;
}