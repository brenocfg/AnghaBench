#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_2__* ops; int /*<<< orphan*/  flags; } ;
struct sixpack {scalar_t__ xleft; int xhead; scalar_t__ tx_enable; TYPE_3__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;
struct TYPE_5__ {int (* write ) (struct tty_struct*,int,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 
 struct sixpack* sp_get (struct tty_struct*) ; 
 int /*<<< orphan*/  sp_put (struct sixpack*) ; 
 int stub1 (struct tty_struct*,int,scalar_t__) ; 

__attribute__((used)) static void sixpack_write_wakeup(struct tty_struct *tty)
{
	struct sixpack *sp = sp_get(tty);
	int actual;

	if (!sp)
		return;
	if (sp->xleft <= 0)  {
		/* Now serial buffer is almost free & we can start
		 * transmission of another packet */
		sp->dev->stats.tx_packets++;
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		sp->tx_enable = 0;
		netif_wake_queue(sp->dev);
		goto out;
	}

	if (sp->tx_enable) {
		actual = tty->ops->write(tty, sp->xhead, sp->xleft);
		sp->xleft -= actual;
		sp->xhead += actual;
	}

out:
	sp_put(sp);
}