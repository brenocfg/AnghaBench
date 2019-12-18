#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {scalar_t__ size; scalar_t__ max_sge; TYPE_4__* wq; int /*<<< orphan*/  lock; } ;
struct ib_srq {int dummy; } ;
struct ipath_srq {TYPE_3__ rq; struct ipath_srq* ip; struct ib_srq ibsrq; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  limit; int /*<<< orphan*/  offset; } ;
struct ipath_rwqe {int dummy; } ;
struct ipath_rwq {int dummy; } ;
struct ipath_ibdev {scalar_t__ n_srqs_allocated; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  n_srqs_lock; } ;
struct ib_udata {int outlen; } ;
struct TYPE_8__ {scalar_t__ max_wr; scalar_t__ max_sge; int /*<<< orphan*/  srq_limit; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; TYPE_2__ attr; } ;
struct ib_sge {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_10__ {scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_7__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct ib_srq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_SRQT_BASIC ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ib_ipath_max_srq_sges ; 
 scalar_t__ ib_ipath_max_srq_wrs ; 
 scalar_t__ ib_ipath_max_srqs ; 
 struct ipath_srq* ipath_create_mmap_info (struct ipath_ibdev*,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct ipath_srq*) ; 
 struct ipath_srq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (TYPE_4__*) ; 
 TYPE_4__* vmalloc_user (int) ; 

struct ib_srq *ipath_create_srq(struct ib_pd *ibpd,
				struct ib_srq_init_attr *srq_init_attr,
				struct ib_udata *udata)
{
	struct ipath_ibdev *dev = to_idev(ibpd->device);
	struct ipath_srq *srq;
	u32 sz;
	struct ib_srq *ret;

	if (srq_init_attr->srq_type != IB_SRQT_BASIC) {
		ret = ERR_PTR(-ENOSYS);
		goto done;
	}

	if (srq_init_attr->attr.max_wr == 0) {
		ret = ERR_PTR(-EINVAL);
		goto done;
	}

	if ((srq_init_attr->attr.max_sge > ib_ipath_max_srq_sges) ||
	    (srq_init_attr->attr.max_wr > ib_ipath_max_srq_wrs)) {
		ret = ERR_PTR(-EINVAL);
		goto done;
	}

	srq = kmalloc(sizeof(*srq), GFP_KERNEL);
	if (!srq) {
		ret = ERR_PTR(-ENOMEM);
		goto done;
	}

	/*
	 * Need to use vmalloc() if we want to support large #s of entries.
	 */
	srq->rq.size = srq_init_attr->attr.max_wr + 1;
	srq->rq.max_sge = srq_init_attr->attr.max_sge;
	sz = sizeof(struct ib_sge) * srq->rq.max_sge +
		sizeof(struct ipath_rwqe);
	srq->rq.wq = vmalloc_user(sizeof(struct ipath_rwq) + srq->rq.size * sz);
	if (!srq->rq.wq) {
		ret = ERR_PTR(-ENOMEM);
		goto bail_srq;
	}

	/*
	 * Return the address of the RWQ as the offset to mmap.
	 * See ipath_mmap() for details.
	 */
	if (udata && udata->outlen >= sizeof(__u64)) {
		int err;
		u32 s = sizeof(struct ipath_rwq) + srq->rq.size * sz;

		srq->ip =
		    ipath_create_mmap_info(dev, s,
					   ibpd->uobject->context,
					   srq->rq.wq);
		if (!srq->ip) {
			ret = ERR_PTR(-ENOMEM);
			goto bail_wq;
		}

		err = ib_copy_to_udata(udata, &srq->ip->offset,
				       sizeof(srq->ip->offset));
		if (err) {
			ret = ERR_PTR(err);
			goto bail_ip;
		}
	} else
		srq->ip = NULL;

	/*
	 * ib_create_srq() will initialize srq->ibsrq.
	 */
	spin_lock_init(&srq->rq.lock);
	srq->rq.wq->head = 0;
	srq->rq.wq->tail = 0;
	srq->limit = srq_init_attr->attr.srq_limit;

	spin_lock(&dev->n_srqs_lock);
	if (dev->n_srqs_allocated == ib_ipath_max_srqs) {
		spin_unlock(&dev->n_srqs_lock);
		ret = ERR_PTR(-ENOMEM);
		goto bail_ip;
	}

 	dev->n_srqs_allocated++;
	spin_unlock(&dev->n_srqs_lock);

	if (srq->ip) {
		spin_lock_irq(&dev->pending_lock);
		list_add(&srq->ip->pending_mmaps, &dev->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);
	}

	ret = &srq->ibsrq;
	goto done;

bail_ip:
	kfree(srq->ip);
bail_wq:
	vfree(srq->rq.wq);
bail_srq:
	kfree(srq);
done:
	return ret;
}