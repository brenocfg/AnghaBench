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
struct net_device {int base_addr; size_t if_port; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct corkscrew_private {int available_media; int default_media; int /*<<< orphan*/  lock; TYPE_2__ timer; } ;
typedef  int __u32 ;
struct TYPE_3__ {int mask; size_t next; int media_bits; int /*<<< orphan*/  name; scalar_t__ wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_CMD ; 
 int Media_10TP ; 
 int Media_LnkBeat ; 
 int Media_SQE ; 
 int StartCoax ; 
 int StopCoax ; 
 scalar_t__ Wn3_Config ; 
 scalar_t__ Wn4_Media ; 
 int Xcvr ; 
 int Xcvr_shift ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int corkscrew_debug ; 
 int inl (scalar_t__) ; 
 int inw (scalar_t__) ; 
 scalar_t__ jiffies ; 
 TYPE_1__* media_tbl ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void corkscrew_timer(unsigned long data)
{
#ifdef AUTOMEDIA
	struct net_device *dev = (struct net_device *) data;
	struct corkscrew_private *vp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	unsigned long flags;
	int ok = 0;

	if (corkscrew_debug > 1)
		pr_debug("%s: Media selection timer tick happened, %s.\n",
		       dev->name, media_tbl[dev->if_port].name);

	spin_lock_irqsave(&vp->lock, flags);

	{
		int old_window = inw(ioaddr + EL3_CMD) >> 13;
		int media_status;
		EL3WINDOW(4);
		media_status = inw(ioaddr + Wn4_Media);
		switch (dev->if_port) {
		case 0:
		case 4:
		case 5:	/* 10baseT, 100baseTX, 100baseFX  */
			if (media_status & Media_LnkBeat) {
				ok = 1;
				if (corkscrew_debug > 1)
					pr_debug("%s: Media %s has link beat, %x.\n",
						dev->name,
						media_tbl[dev->if_port].name,
						media_status);
			} else if (corkscrew_debug > 1)
				pr_debug("%s: Media %s is has no link beat, %x.\n",
					dev->name,
					media_tbl[dev->if_port].name,
					media_status);

			break;
		default:	/* Other media types handled by Tx timeouts. */
			if (corkscrew_debug > 1)
				pr_debug("%s: Media %s is has no indication, %x.\n",
					dev->name,
					media_tbl[dev->if_port].name,
					media_status);
			ok = 1;
		}
		if (!ok) {
			__u32 config;

			do {
				dev->if_port =
				    media_tbl[dev->if_port].next;
			}
			while (!(vp->available_media & media_tbl[dev->if_port].mask));

			if (dev->if_port == 8) {	/* Go back to default. */
				dev->if_port = vp->default_media;
				if (corkscrew_debug > 1)
					pr_debug("%s: Media selection failing, using default %s port.\n",
						dev->name,
						media_tbl[dev->if_port].name);
			} else {
				if (corkscrew_debug > 1)
					pr_debug("%s: Media selection failed, now trying %s port.\n",
						dev->name,
						media_tbl[dev->if_port].name);
				vp->timer.expires = jiffies + media_tbl[dev->if_port].wait;
				add_timer(&vp->timer);
			}
			outw((media_status & ~(Media_10TP | Media_SQE)) |
			     media_tbl[dev->if_port].media_bits,
			     ioaddr + Wn4_Media);

			EL3WINDOW(3);
			config = inl(ioaddr + Wn3_Config);
			config = (config & ~Xcvr) | (dev->if_port << Xcvr_shift);
			outl(config, ioaddr + Wn3_Config);

			outw(dev->if_port == 3 ? StartCoax : StopCoax,
			     ioaddr + EL3_CMD);
		}
		EL3WINDOW(old_window);
	}

	spin_unlock_irqrestore(&vp->lock, flags);
	if (corkscrew_debug > 1)
		pr_debug("%s: Media selection timer finished, %s.\n",
		       dev->name, media_tbl[dev->if_port].name);

#endif				/* AUTOMEDIA */
	return;
}