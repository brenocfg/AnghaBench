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
struct tty_struct {int receive_room; struct sixpack* disc_data; TYPE_1__* ops; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct sixpack {char* rbuff; char* xbuff; unsigned long buffsize; int led_state; int status; int status1; int /*<<< orphan*/  lock; TYPE_2__ resync_t; TYPE_2__ tx_t; scalar_t__ tx_enable; scalar_t__ status2; int /*<<< orphan*/  slottime; int /*<<< orphan*/  persistence; int /*<<< orphan*/  tx_delay; scalar_t__ duplex; scalar_t__ flags; scalar_t__ xleft; scalar_t__ rx_count_cooked; scalar_t__ rx_count; scalar_t__ rcount; scalar_t__ mtu; struct tty_struct* tty; int /*<<< orphan*/  dead_sem; int /*<<< orphan*/  refcnt; struct net_device* dev; } ;
struct net_device {int mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 scalar_t__ AX25_MTU ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIXP_PERSIST ; 
 int /*<<< orphan*/  SIXP_SLOTTIME ; 
 int /*<<< orphan*/  SIXP_TXDELAY ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_MUTEX_LOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 struct sixpack* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  sp_setup ; 
 int /*<<< orphan*/  sp_xmit_on_air ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tnc_init (struct sixpack*) ; 

__attribute__((used)) static int sixpack_open(struct tty_struct *tty)
{
	char *rbuff = NULL, *xbuff = NULL;
	struct net_device *dev;
	struct sixpack *sp;
	unsigned long len;
	int err = 0;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;
	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	dev = alloc_netdev(sizeof(struct sixpack), "sp%d", sp_setup);
	if (!dev) {
		err = -ENOMEM;
		goto out;
	}

	sp = netdev_priv(dev);
	sp->dev = dev;

	spin_lock_init(&sp->lock);
	atomic_set(&sp->refcnt, 1);
	init_MUTEX_LOCKED(&sp->dead_sem);

	/* !!! length of the buffers. MTU is IP MTU, not PACLEN!  */

	len = dev->mtu * 2;

	rbuff = kmalloc(len + 4, GFP_KERNEL);
	xbuff = kmalloc(len + 4, GFP_KERNEL);

	if (rbuff == NULL || xbuff == NULL) {
		err = -ENOBUFS;
		goto out_free;
	}

	spin_lock_bh(&sp->lock);

	sp->tty = tty;

	sp->rbuff	= rbuff;
	sp->xbuff	= xbuff;

	sp->mtu		= AX25_MTU + 73;
	sp->buffsize	= len;
	sp->rcount	= 0;
	sp->rx_count	= 0;
	sp->rx_count_cooked = 0;
	sp->xleft	= 0;

	sp->flags	= 0;		/* Clear ESCAPE & ERROR flags */

	sp->duplex	= 0;
	sp->tx_delay    = SIXP_TXDELAY;
	sp->persistence = SIXP_PERSIST;
	sp->slottime    = SIXP_SLOTTIME;
	sp->led_state   = 0x60;
	sp->status      = 1;
	sp->status1     = 1;
	sp->status2     = 0;
	sp->tx_enable   = 0;

	netif_start_queue(dev);

	init_timer(&sp->tx_t);
	sp->tx_t.function = sp_xmit_on_air;
	sp->tx_t.data = (unsigned long) sp;

	init_timer(&sp->resync_t);

	spin_unlock_bh(&sp->lock);

	/* Done.  We have linked the TTY line to a channel. */
	tty->disc_data = sp;
	tty->receive_room = 65536;

	/* Now we're ready to register. */
	if (register_netdev(dev))
		goto out_free;

	tnc_init(sp);

	return 0;

out_free:
	kfree(xbuff);
	kfree(rbuff);

	if (dev)
		free_netdev(dev);

out:
	return err;
}