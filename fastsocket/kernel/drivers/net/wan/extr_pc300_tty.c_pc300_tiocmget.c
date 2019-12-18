#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {scalar_t__ driver_data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct TYPE_9__ {TYPE_3__* pc300dev; } ;
typedef  TYPE_2__ st_cpc_tty_area ;
struct TYPE_10__ {scalar_t__ hdlc; scalar_t__ chan; } ;
typedef  TYPE_3__ pc300dev_t ;
struct TYPE_11__ {int channel; scalar_t__ card; } ;
typedef  TYPE_4__ pc300ch_t ;
struct TYPE_8__ {scalar_t__ scabase; } ;
struct TYPE_12__ {TYPE_1__ hw; } ;
typedef  TYPE_5__ pc300_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_TTY_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPC_TTY_LOCK (TYPE_5__*,unsigned long) ; 
 int /*<<< orphan*/  CPC_TTY_UNLOCK (TYPE_5__*,unsigned long) ; 
 int /*<<< orphan*/  CTL ; 
 unsigned char CTL_DTR ; 
 unsigned char CTL_RTS ; 
 scalar_t__ M_REG (int /*<<< orphan*/ ,int) ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 unsigned char cpc_readb (scalar_t__) ; 

__attribute__((used)) static int pc300_tiocmget(struct tty_struct *tty, struct file *file)
{
	unsigned int result;
	unsigned char status;
	unsigned long flags;
	st_cpc_tty_area  *cpc_tty = (st_cpc_tty_area *) tty->driver_data;
	pc300dev_t *pc300dev = cpc_tty->pc300dev;
	pc300ch_t *pc300chan = (pc300ch_t *)pc300dev->chan;
	pc300_t *card = (pc300_t *) pc300chan->card;
	int ch = pc300chan->channel;

	cpc_tty = (st_cpc_tty_area *) tty->driver_data;

	CPC_TTY_DBG("%s-tty: tiocmget\n",
		((struct net_device*)(pc300dev->hdlc))->name);

	CPC_TTY_LOCK(card, flags);
	status = cpc_readb(card->hw.scabase+M_REG(CTL,ch));
	CPC_TTY_UNLOCK(card,flags);

	result = ((status & CTL_DTR) ? TIOCM_DTR : 0) |
		 ((status & CTL_RTS) ? TIOCM_RTS : 0);

	return result;
}