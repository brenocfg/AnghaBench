#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct x25_asy {scalar_t__ magic; TYPE_2__* dev; struct tty_struct* tty; } ;
struct tty_struct {int receive_room; struct x25_asy* disc_data; TYPE_1__* ops; } ;
struct TYPE_4__ {int base_addr; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_X25 ; 
 int EEXIST ; 
 int ENFILE ; 
 int EOPNOTSUPP ; 
 scalar_t__ X25_ASY_MAGIC ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 struct x25_asy* x25_asy_alloc () ; 
 int x25_asy_open (TYPE_2__*) ; 

__attribute__((used)) static int x25_asy_open_tty(struct tty_struct *tty)
{
	struct x25_asy *sl = tty->disc_data;
	int err;

	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	/* First make sure we're not already connected. */
	if (sl && sl->magic == X25_ASY_MAGIC)
		return -EEXIST;

	/* OK.  Find a free X.25 channel to use. */
	sl = x25_asy_alloc();
	if (sl == NULL)
		return -ENFILE;

	sl->tty = tty;
	tty->disc_data = sl;
	tty->receive_room = 65536;
	tty_driver_flush_buffer(tty);
	tty_ldisc_flush(tty);

	/* Restore default settings */
	sl->dev->type = ARPHRD_X25;

	/* Perform the low-level X.25 async init */
	err = x25_asy_open(sl->dev);
	if (err)
		return err;
	/* Done.  We have linked the TTY line to a channel. */
	return sl->dev->base_addr;
}