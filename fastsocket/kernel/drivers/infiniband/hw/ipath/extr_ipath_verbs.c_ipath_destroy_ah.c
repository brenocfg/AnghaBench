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
struct ipath_ibdev {int /*<<< orphan*/  n_ahs_lock; int /*<<< orphan*/  n_ahs_allocated; } ;
struct ipath_ah {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipath_ah*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipath_ah* to_iah (struct ib_ah*) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipath_destroy_ah(struct ib_ah *ibah)
{
	struct ipath_ibdev *dev = to_idev(ibah->device);
	struct ipath_ah *ah = to_iah(ibah);
	unsigned long flags;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	dev->n_ahs_allocated--;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	kfree(ah);

	return 0;
}