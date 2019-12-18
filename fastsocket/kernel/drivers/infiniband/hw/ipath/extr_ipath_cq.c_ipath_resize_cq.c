#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipath_mmap_info {int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  offset; } ;
struct ipath_ibdev {int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; } ;
struct ipath_cq_wc {int head; int tail; int /*<<< orphan*/ * kqueue; int /*<<< orphan*/ * uqueue; } ;
struct TYPE_2__ {int cqe; } ;
struct ipath_cq {int /*<<< orphan*/  lock; struct ipath_mmap_info* ip; struct ipath_cq_wc* queue; TYPE_1__ ibcq; } ;
struct ib_wc {int dummy; } ;
struct ib_uverbs_wc {int dummy; } ;
struct ib_udata {int outlen; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  offset ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int ib_ipath_max_cqes ; 
 int /*<<< orphan*/  ipath_update_mmap_info (struct ipath_ibdev*,struct ipath_mmap_info*,int,struct ipath_cq_wc*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct ipath_cq* to_icq (struct ib_cq*) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfree (struct ipath_cq_wc*) ; 
 struct ipath_cq_wc* vmalloc_user (int) ; 

int ipath_resize_cq(struct ib_cq *ibcq, int cqe, struct ib_udata *udata)
{
	struct ipath_cq *cq = to_icq(ibcq);
	struct ipath_cq_wc *old_wc;
	struct ipath_cq_wc *wc;
	u32 head, tail, n;
	int ret;
	u32 sz;

	if (cqe < 1 || cqe > ib_ipath_max_cqes) {
		ret = -EINVAL;
		goto bail;
	}

	/*
	 * Need to use vmalloc() if we want to support large #s of entries.
	 */
	sz = sizeof(*wc);
	if (udata && udata->outlen >= sizeof(__u64))
		sz += sizeof(struct ib_uverbs_wc) * (cqe + 1);
	else
		sz += sizeof(struct ib_wc) * (cqe + 1);
	wc = vmalloc_user(sz);
	if (!wc) {
		ret = -ENOMEM;
		goto bail;
	}

	/* Check that we can write the offset to mmap. */
	if (udata && udata->outlen >= sizeof(__u64)) {
		__u64 offset = 0;

		ret = ib_copy_to_udata(udata, &offset, sizeof(offset));
		if (ret)
			goto bail_free;
	}

	spin_lock_irq(&cq->lock);
	/*
	 * Make sure head and tail are sane since they
	 * might be user writable.
	 */
	old_wc = cq->queue;
	head = old_wc->head;
	if (head > (u32) cq->ibcq.cqe)
		head = (u32) cq->ibcq.cqe;
	tail = old_wc->tail;
	if (tail > (u32) cq->ibcq.cqe)
		tail = (u32) cq->ibcq.cqe;
	if (head < tail)
		n = cq->ibcq.cqe + 1 + head - tail;
	else
		n = head - tail;
	if (unlikely((u32)cqe < n)) {
		ret = -EINVAL;
		goto bail_unlock;
	}
	for (n = 0; tail != head; n++) {
		if (cq->ip)
			wc->uqueue[n] = old_wc->uqueue[tail];
		else
			wc->kqueue[n] = old_wc->kqueue[tail];
		if (tail == (u32) cq->ibcq.cqe)
			tail = 0;
		else
			tail++;
	}
	cq->ibcq.cqe = cqe;
	wc->head = n;
	wc->tail = 0;
	cq->queue = wc;
	spin_unlock_irq(&cq->lock);

	vfree(old_wc);

	if (cq->ip) {
		struct ipath_ibdev *dev = to_idev(ibcq->device);
		struct ipath_mmap_info *ip = cq->ip;

		ipath_update_mmap_info(dev, ip, sz, wc);

		/*
		 * Return the offset to mmap.
		 * See ipath_mmap() for details.
		 */
		if (udata && udata->outlen >= sizeof(__u64)) {
			ret = ib_copy_to_udata(udata, &ip->offset,
					       sizeof(ip->offset));
			if (ret)
				goto bail;
		}

		spin_lock_irq(&dev->pending_lock);
		if (list_empty(&ip->pending_mmaps))
			list_add(&ip->pending_mmaps, &dev->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);
	}

	ret = 0;
	goto bail;

bail_unlock:
	spin_unlock_irq(&cq->lock);
bail_free:
	vfree(wc);
bail:
	return ret;
}