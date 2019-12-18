#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct b44 {TYPE_1__ timer; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_CHIP_RESET_PARTIAL ; 
 int /*<<< orphan*/  B44_FULL_RESET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int b44_alloc_consistent (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_check_phy (struct b44*) ; 
 int /*<<< orphan*/  b44_chip_reset (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_enable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_free_consistent (struct b44*) ; 
 int /*<<< orphan*/  b44_free_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_init_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_interrupt ; 
 int /*<<< orphan*/  b44_timer ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int b44_open(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);
	int err;

	err = b44_alloc_consistent(bp, GFP_KERNEL);
	if (err)
		goto out;

	napi_enable(&bp->napi);

	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);

	b44_check_phy(bp);

	err = request_irq(dev->irq, b44_interrupt, IRQF_SHARED, dev->name, dev);
	if (unlikely(err < 0)) {
		napi_disable(&bp->napi);
		b44_chip_reset(bp, B44_CHIP_RESET_PARTIAL);
		b44_free_rings(bp);
		b44_free_consistent(bp);
		goto out;
	}

	init_timer(&bp->timer);
	bp->timer.expires = jiffies + HZ;
	bp->timer.data = (unsigned long) bp;
	bp->timer.function = b44_timer;
	add_timer(&bp->timer);

	b44_enable_ints(bp);
	netif_start_queue(dev);
out:
	return err;
}