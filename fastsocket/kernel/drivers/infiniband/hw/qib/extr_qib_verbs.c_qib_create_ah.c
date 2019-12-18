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
struct qib_ibdev {scalar_t__ n_ahs_allocated; int /*<<< orphan*/  n_ahs_lock; } ;
struct ib_ah {int dummy; } ;
struct ib_ah_attr {int dummy; } ;
struct qib_ah {struct ib_ah ibah; int /*<<< orphan*/  refcount; struct ib_ah_attr attr; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_qib_max_ahs ; 
 int /*<<< orphan*/  kfree (struct qib_ah*) ; 
 struct qib_ah* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qib_check_ah (int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ah *qib_create_ah(struct ib_pd *pd,
				   struct ib_ah_attr *ah_attr)
{
	struct qib_ah *ah;
	struct ib_ah *ret;
	struct qib_ibdev *dev = to_idev(pd->device);
	unsigned long flags;

	if (qib_check_ah(pd->device, ah_attr)) {
		ret = ERR_PTR(-EINVAL);
		goto bail;
	}

	ah = kmalloc(sizeof *ah, GFP_ATOMIC);
	if (!ah) {
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	if (dev->n_ahs_allocated == ib_qib_max_ahs) {
		spin_unlock_irqrestore(&dev->n_ahs_lock, flags);
		kfree(ah);
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	dev->n_ahs_allocated++;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	/* ib_create_ah() will initialize ah->ibah. */
	ah->attr = *ah_attr;
	atomic_set(&ah->refcount, 0);

	ret = &ah->ibah;

bail:
	return ret;
}