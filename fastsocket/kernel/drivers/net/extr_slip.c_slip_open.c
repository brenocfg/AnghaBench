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
struct tty_struct {int receive_room; struct slip* disc_data; TYPE_1__* ops; } ;
struct TYPE_8__ {void* expires; } ;
struct slip {scalar_t__ magic; int keepalive; int outfill; int /*<<< orphan*/  flags; struct tty_struct* tty; TYPE_2__* dev; TYPE_4__ outfill_timer; TYPE_4__ keepalive_timer; int /*<<< orphan*/  pid; int /*<<< orphan*/  line; } ;
struct TYPE_7__ {int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {int base_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int ENFILE ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  SLF_INUSE ; 
 scalar_t__ SLIP_MAGIC ; 
 int /*<<< orphan*/  SL_MTU ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 void* jiffies ; 
 int register_netdevice (TYPE_2__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct slip* sl_alloc (int /*<<< orphan*/ ) ; 
 int sl_alloc_bufs (struct slip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_free_bufs (struct slip*) ; 
 int /*<<< orphan*/  sl_sync () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_devnum (struct tty_struct*) ; 

__attribute__((used)) static int slip_open(struct tty_struct *tty)
{
	struct slip *sl;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	/* RTnetlink lock is misused here to serialize concurrent
	   opens of slip channels. There are better ways, but it is
	   the simplest one.
	 */
	rtnl_lock();

	/* Collect hanged up channels. */
	sl_sync();

	sl = tty->disc_data;

	err = -EEXIST;
	/* First make sure we're not already connected. */
	if (sl && sl->magic == SLIP_MAGIC)
		goto err_exit;

	/* OK.  Find a free SLIP channel to use. */
	err = -ENFILE;
	sl = sl_alloc(tty_devnum(tty));
	if (sl == NULL)
		goto err_exit;

	sl->tty = tty;
	tty->disc_data = sl;
	sl->line = tty_devnum(tty);
	sl->pid = current->pid;

	if (!test_bit(SLF_INUSE, &sl->flags)) {
		/* Perform the low-level SLIP initialization. */
		err = sl_alloc_bufs(sl, SL_MTU);
		if (err)
			goto err_free_chan;

		set_bit(SLF_INUSE, &sl->flags);

		err = register_netdevice(sl->dev);
		if (err)
			goto err_free_bufs;
	}

#ifdef CONFIG_SLIP_SMART
	if (sl->keepalive) {
		sl->keepalive_timer.expires = jiffies + sl->keepalive * HZ;
		add_timer(&sl->keepalive_timer);
	}
	if (sl->outfill) {
		sl->outfill_timer.expires = jiffies + sl->outfill * HZ;
		add_timer(&sl->outfill_timer);
	}
#endif

	/* Done.  We have linked the TTY line to a channel. */
	rtnl_unlock();
	tty->receive_room = 65536;	/* We don't flow control */
	return sl->dev->base_addr;

err_free_bufs:
	sl_free_bufs(sl);

err_free_chan:
	sl->tty = NULL;
	tty->disc_data = NULL;
	clear_bit(SLF_INUSE, &sl->flags);

err_exit:
	rtnl_unlock();

	/* Count references from TTY module */
	return err;
}