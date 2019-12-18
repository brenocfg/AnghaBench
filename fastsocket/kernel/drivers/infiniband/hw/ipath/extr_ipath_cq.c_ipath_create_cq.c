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
typedef  int u32 ;
struct ipath_ibdev {scalar_t__ n_cqs_allocated; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  n_cqs_lock; } ;
struct ipath_cq_wc {scalar_t__ tail; scalar_t__ head; } ;
struct ib_cq {int cqe; } ;
struct ipath_cq {struct ipath_cq* ip; struct ib_cq ibcq; struct ipath_cq_wc* queue; int /*<<< orphan*/  comptask; int /*<<< orphan*/  lock; scalar_t__ triggered; int /*<<< orphan*/  notify; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  offset; } ;
struct ib_wc {int dummy; } ;
struct ib_uverbs_wc {int dummy; } ;
struct ib_udata {int outlen; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CQ_NONE ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int ib_ipath_max_cqes ; 
 scalar_t__ ib_ipath_max_cqs ; 
 struct ipath_cq* ipath_create_mmap_info (struct ipath_ibdev*,int,struct ib_ucontext*,struct ipath_cq_wc*) ; 
 int /*<<< orphan*/  kfree (struct ipath_cq*) ; 
 struct ipath_cq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_complete ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 
 int /*<<< orphan*/  vfree (struct ipath_cq_wc*) ; 
 struct ipath_cq_wc* vmalloc_user (int) ; 

struct ib_cq *ipath_create_cq(struct ib_device *ibdev, int entries, int comp_vector,
			      struct ib_ucontext *context,
			      struct ib_udata *udata)
{
	struct ipath_ibdev *dev = to_idev(ibdev);
	struct ipath_cq *cq;
	struct ipath_cq_wc *wc;
	struct ib_cq *ret;
	u32 sz;

	if (entries < 1 || entries > ib_ipath_max_cqes) {
		ret = ERR_PTR(-EINVAL);
		goto done;
	}

	/* Allocate the completion queue structure. */
	cq = kmalloc(sizeof(*cq), GFP_KERNEL);
	if (!cq) {
		ret = ERR_PTR(-ENOMEM);
		goto done;
	}

	/*
	 * Allocate the completion queue entries and head/tail pointers.
	 * This is allocated separately so that it can be resized and
	 * also mapped into user space.
	 * We need to use vmalloc() in order to support mmap and large
	 * numbers of entries.
	 */
	sz = sizeof(*wc);
	if (udata && udata->outlen >= sizeof(__u64))
		sz += sizeof(struct ib_uverbs_wc) * (entries + 1);
	else
		sz += sizeof(struct ib_wc) * (entries + 1);
	wc = vmalloc_user(sz);
	if (!wc) {
		ret = ERR_PTR(-ENOMEM);
		goto bail_cq;
	}

	/*
	 * Return the address of the WC as the offset to mmap.
	 * See ipath_mmap() for details.
	 */
	if (udata && udata->outlen >= sizeof(__u64)) {
		int err;

		cq->ip = ipath_create_mmap_info(dev, sz, context, wc);
		if (!cq->ip) {
			ret = ERR_PTR(-ENOMEM);
			goto bail_wc;
		}

		err = ib_copy_to_udata(udata, &cq->ip->offset,
				       sizeof(cq->ip->offset));
		if (err) {
			ret = ERR_PTR(err);
			goto bail_ip;
		}
	} else
		cq->ip = NULL;

	spin_lock(&dev->n_cqs_lock);
	if (dev->n_cqs_allocated == ib_ipath_max_cqs) {
		spin_unlock(&dev->n_cqs_lock);
		ret = ERR_PTR(-ENOMEM);
		goto bail_ip;
	}

	dev->n_cqs_allocated++;
	spin_unlock(&dev->n_cqs_lock);

	if (cq->ip) {
		spin_lock_irq(&dev->pending_lock);
		list_add(&cq->ip->pending_mmaps, &dev->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);
	}

	/*
	 * ib_create_cq() will initialize cq->ibcq except for cq->ibcq.cqe.
	 * The number of entries should be >= the number requested or return
	 * an error.
	 */
	cq->ibcq.cqe = entries;
	cq->notify = IB_CQ_NONE;
	cq->triggered = 0;
	spin_lock_init(&cq->lock);
	tasklet_init(&cq->comptask, send_complete, (unsigned long)cq);
	wc->head = 0;
	wc->tail = 0;
	cq->queue = wc;

	ret = &cq->ibcq;

	goto done;

bail_ip:
	kfree(cq->ip);
bail_wc:
	vfree(wc);
bail_cq:
	kfree(cq);
done:
	return ret;
}