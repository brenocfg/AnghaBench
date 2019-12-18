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
typedef  int /*<<< orphan*/  u64 ;
struct mthca_srq {int max; int wqe_shift; void* last; int /*<<< orphan*/  wrid; int /*<<< orphan*/  mr; int /*<<< orphan*/  is_direct; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {scalar_t__ uobject; } ;
struct mthca_pd {TYPE_1__ ibpd; } ;
struct mthca_next_seg {scalar_t__ nda_op; } ;
struct mthca_dev {int dummy; } ;
struct mthca_data_seg {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTHCA_INVAL_LKEY ; 
 int /*<<< orphan*/  MTHCA_MAX_DIRECT_SRQ_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* get_wqe (struct mthca_srq*,int) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_buf_alloc (struct mthca_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mthca_pd*,int,int /*<<< orphan*/ *) ; 
 int* wqe_to_link (void*) ; 

__attribute__((used)) static int mthca_alloc_srq_buf(struct mthca_dev *dev, struct mthca_pd *pd,
			       struct mthca_srq *srq)
{
	struct mthca_data_seg *scatter;
	void *wqe;
	int err;
	int i;

	if (pd->ibpd.uobject)
		return 0;

	srq->wrid = kmalloc(srq->max * sizeof (u64), GFP_KERNEL);
	if (!srq->wrid)
		return -ENOMEM;

	err = mthca_buf_alloc(dev, srq->max << srq->wqe_shift,
			      MTHCA_MAX_DIRECT_SRQ_SIZE,
			      &srq->queue, &srq->is_direct, pd, 1, &srq->mr);
	if (err) {
		kfree(srq->wrid);
		return err;
	}

	/*
	 * Now initialize the SRQ buffer so that all of the WQEs are
	 * linked into the list of free WQEs.  In addition, set the
	 * scatter list L_Keys to the sentry value of 0x100.
	 */
	for (i = 0; i < srq->max; ++i) {
		struct mthca_next_seg *next;

		next = wqe = get_wqe(srq, i);

		if (i < srq->max - 1) {
			*wqe_to_link(wqe) = i + 1;
			next->nda_op = htonl(((i + 1) << srq->wqe_shift) | 1);
		} else {
			*wqe_to_link(wqe) = -1;
			next->nda_op = 0;
		}

		for (scatter = wqe + sizeof (struct mthca_next_seg);
		     (void *) scatter < wqe + (1 << srq->wqe_shift);
		     ++scatter)
			scatter->lkey = cpu_to_be32(MTHCA_INVAL_LKEY);
	}

	srq->last = get_wqe(srq, srq->max - 1);

	return 0;
}