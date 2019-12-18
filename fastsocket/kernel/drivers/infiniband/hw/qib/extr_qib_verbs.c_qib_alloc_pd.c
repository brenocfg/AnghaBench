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
struct ib_pd {int dummy; } ;
struct qib_pd {struct ib_pd ibpd; int /*<<< orphan*/  user; } ;
struct qib_ibdev {scalar_t__ n_pds_allocated; int /*<<< orphan*/  n_pds_lock; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_pd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_qib_max_pds ; 
 int /*<<< orphan*/  kfree (struct qib_pd*) ; 
 struct qib_pd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static struct ib_pd *qib_alloc_pd(struct ib_device *ibdev,
				  struct ib_ucontext *context,
				  struct ib_udata *udata)
{
	struct qib_ibdev *dev = to_idev(ibdev);
	struct qib_pd *pd;
	struct ib_pd *ret;

	/*
	 * This is actually totally arbitrary.  Some correctness tests
	 * assume there's a maximum number of PDs that can be allocated.
	 * We don't actually have this limit, but we fail the test if
	 * we allow allocations of more than we report for this value.
	 */

	pd = kmalloc(sizeof *pd, GFP_KERNEL);
	if (!pd) {
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	spin_lock(&dev->n_pds_lock);
	if (dev->n_pds_allocated == ib_qib_max_pds) {
		spin_unlock(&dev->n_pds_lock);
		kfree(pd);
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	dev->n_pds_allocated++;
	spin_unlock(&dev->n_pds_lock);

	/* ib_alloc_pd() will initialize pd->ibpd. */
	pd->user = udata != NULL;

	ret = &pd->ibpd;

bail:
	return ret;
}