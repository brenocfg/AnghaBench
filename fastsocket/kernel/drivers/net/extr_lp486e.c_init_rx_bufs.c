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
struct net_device {int dummy; } ;
struct i596_rfd {int size; TYPE_2__* rbd; void* pa_next; scalar_t__ cmd; scalar_t__ count; void* pa_rbd; scalar_t__ stat; } ;
struct i596_rbd {int dummy; } ;
struct TYPE_3__ {void* pa_rfd; } ;
struct i596_private {TYPE_2__* rbd_tail; TYPE_1__ scb; struct i596_rfd* rx_tail; } ;
struct TYPE_4__ {struct TYPE_4__* next; void* size; struct TYPE_4__* prev; int /*<<< orphan*/  skb; scalar_t__ count; scalar_t__ pad; } ;

/* Variables and functions */
 scalar_t__ CMD_EOL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* I596_NULL ; 
 void* RBD_EL ; 
 int RX_RBD_SIZE ; 
 void* RX_SKBSIZE ; 
 int /*<<< orphan*/  dev_alloc_skb (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_2__* rbd ; 
 void* va_to_pa (struct i596_rfd*) ; 

__attribute__((used)) static inline int
init_rx_bufs(struct net_device *dev, int num) {
	struct i596_private *lp;
	struct i596_rfd *rfd;
	int i;
	// struct i596_rbd *rbd;

	lp = netdev_priv(dev);
	lp->scb.pa_rfd = I596_NULL;

	for (i = 0; i < num; i++) {
		rfd = kmalloc(sizeof(struct i596_rfd), GFP_KERNEL);
		if (rfd == NULL)
			break;

		rfd->stat = 0;
		rfd->pa_rbd = I596_NULL;
		rfd->count = 0;
		rfd->size = 1532;
		if (i == 0) {
			rfd->cmd = CMD_EOL;
			lp->rx_tail = rfd;
		} else {
			rfd->cmd = 0;
		}
		rfd->pa_next = lp->scb.pa_rfd;
		lp->scb.pa_rfd = va_to_pa(rfd);
		lp->rx_tail->pa_next = lp->scb.pa_rfd;
	}

#if 0
	for (i = 0; i<RX_RBD_SIZE; i++) {
		rbd = kmalloc(sizeof(struct i596_rbd), GFP_KERNEL);
		if (rbd) {
			rbd->pad = 0;
			rbd->count = 0;
			rbd->skb = dev_alloc_skb(RX_SKBSIZE);
			if (!rbd->skb) {
				printk("dev_alloc_skb failed");
			}
			rbd->next = rfd->rbd;
			if (i) {
				rfd->rbd->prev = rbd;
				rbd->size = RX_SKBSIZE;
			} else {
				rbd->size = (RX_SKBSIZE | RBD_EL);
				lp->rbd_tail = rbd;
			}

			rfd->rbd = rbd;
		} else {
			printk("Could not kmalloc rbd\n");
		}
	}
	lp->rbd_tail->next = rfd->rbd;
#endif
	return (i);
}