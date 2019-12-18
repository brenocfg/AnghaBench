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
struct tty_struct {TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct mkiss {scalar_t__ xleft; int xhead; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,int,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mkiss* mkiss_get (struct tty_struct*) ; 
 int /*<<< orphan*/  mkiss_put (struct mkiss*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int stub1 (struct tty_struct*,int,scalar_t__) ; 

__attribute__((used)) static void mkiss_write_wakeup(struct tty_struct *tty)
{
	struct mkiss *ax = mkiss_get(tty);
	int actual;

	if (!ax)
		return;

	if (ax->xleft <= 0)  {
		/* Now serial buffer is almost free & we can start
		 * transmission of another packet
		 */
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

		netif_wake_queue(ax->dev);
		goto out;
	}

	actual = tty->ops->write(tty, ax->xhead, ax->xleft);
	ax->xleft -= actual;
	ax->xhead += actual;

out:
	mkiss_put(ax);
}