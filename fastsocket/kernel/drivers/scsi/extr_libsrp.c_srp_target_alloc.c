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
struct srp_target {size_t srp_iu_size; size_t rx_ring_size; int /*<<< orphan*/  rx_ring; struct device* dev; int /*<<< orphan*/  iu_queue; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct srp_target*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int srp_iu_pool_alloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_ring_alloc (struct device*,size_t,size_t) ; 
 int /*<<< orphan*/  srp_ring_free (struct device*,int /*<<< orphan*/ ,size_t,size_t) ; 

int srp_target_alloc(struct srp_target *target, struct device *dev,
		     size_t nr, size_t iu_size)
{
	int err;

	spin_lock_init(&target->lock);
	INIT_LIST_HEAD(&target->cmd_queue);

	target->dev = dev;
	dev_set_drvdata(target->dev, target);

	target->srp_iu_size = iu_size;
	target->rx_ring_size = nr;
	target->rx_ring = srp_ring_alloc(target->dev, nr, iu_size);
	if (!target->rx_ring)
		return -ENOMEM;
	err = srp_iu_pool_alloc(&target->iu_queue, nr, target->rx_ring);
	if (err)
		goto free_ring;

	return 0;

free_ring:
	srp_ring_free(target->dev, target->rx_ring, nr, iu_size);
	return -ENOMEM;
}