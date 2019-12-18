#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct plip_local {int /*<<< orphan*/ * skb; void* state; } ;
struct net_local {scalar_t__ port_owner; int /*<<< orphan*/  pardev; int /*<<< orphan*/  connection; scalar_t__ is_deferred; int /*<<< orphan*/  killed_timer_cmp; int /*<<< orphan*/  kill_timer; struct plip_local rcv_data; struct plip_local snd_data; } ;
struct net_device {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE (int) ; 
 int /*<<< orphan*/  PAR_CONTROL (struct net_device*) ; 
 int /*<<< orphan*/  PAR_DATA (struct net_device*) ; 
 int /*<<< orphan*/  PLIP_CN_NONE ; 
 void* PLIP_PK_DONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
plip_close(struct net_device *dev)
{
	struct net_local *nl = netdev_priv(dev);
	struct plip_local *snd = &nl->snd_data;
	struct plip_local *rcv = &nl->rcv_data;

	netif_stop_queue (dev);
	DISABLE(dev->irq);
	synchronize_irq(dev->irq);

	if (dev->irq == -1)
	{
		init_completion(&nl->killed_timer_cmp);
		atomic_set (&nl->kill_timer, 1);
		wait_for_completion(&nl->killed_timer_cmp);
	}

#ifdef NOTDEF
	outb(0x00, PAR_DATA(dev));
#endif
	nl->is_deferred = 0;
	nl->connection = PLIP_CN_NONE;
	if (nl->port_owner) {
		parport_release(nl->pardev);
		nl->port_owner = 0;
	}

	snd->state = PLIP_PK_DONE;
	if (snd->skb) {
		dev_kfree_skb(snd->skb);
		snd->skb = NULL;
	}
	rcv->state = PLIP_PK_DONE;
	if (rcv->skb) {
		kfree_skb(rcv->skb);
		rcv->skb = NULL;
	}

#ifdef NOTDEF
	/* Reset. */
	outb(0x00, PAR_CONTROL(dev));
#endif
	return 0;
}