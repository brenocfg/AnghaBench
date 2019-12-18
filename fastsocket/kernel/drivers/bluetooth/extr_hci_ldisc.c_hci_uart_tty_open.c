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
struct tty_struct {int receive_room; TYPE_3__* ldisc; struct hci_uart* disc_data; TYPE_1__* ops; } ;
struct hci_uart {int /*<<< orphan*/  rx_lock; struct tty_struct* tty; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EEXIST ; 
 int ENFILE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hci_uart* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static int hci_uart_tty_open(struct tty_struct *tty)
{
	struct hci_uart *hu = (void *) tty->disc_data;

	BT_DBG("tty %p", tty);

	/* FIXME: This btw is bogus, nothing requires the old ldisc to clear
	   the pointer */
	if (hu)
		return -EEXIST;

	/* Error if the tty has no write op instead of leaving an exploitable
	   hole */
	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	if (!(hu = kzalloc(sizeof(struct hci_uart), GFP_KERNEL))) {
		BT_ERR("Can't allocate control structure");
		return -ENFILE;
	}

	tty->disc_data = hu;
	hu->tty = tty;
	tty->receive_room = 65536;

	spin_lock_init(&hu->rx_lock);

	/* Flush any pending characters in the driver and line discipline. */

	/* FIXME: why is this needed. Note don't use ldisc_ref here as the
	   open path is before the ldisc is referencable */

	if (tty->ldisc->ops->flush_buffer)
		tty->ldisc->ops->flush_buffer(tty);
	tty_driver_flush_buffer(tty);

	return 0;
}