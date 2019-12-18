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
struct priv {int /*<<< orphan*/ ** tmd_skb; } ;
struct net_device {int /*<<< orphan*/  irq; struct priv* ml_priv; } ;

/* Variables and functions */
 scalar_t__ L_RESET ; 
 scalar_t__ PORT ; 
 int TMDNUM ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ni65_close(struct net_device *dev)
{
	struct priv *p = dev->ml_priv;

	netif_stop_queue(dev);

	outw(inw(PORT+L_RESET),PORT+L_RESET); /* that's the hard way */

#ifdef XMT_VIA_SKB
	{
		int i;
		for(i=0;i<TMDNUM;i++)
		{
			if(p->tmd_skb[i]) {
				dev_kfree_skb(p->tmd_skb[i]);
				p->tmd_skb[i] = NULL;
			}
		}
	}
#endif
	free_irq(dev->irq,dev);
	return 0;
}