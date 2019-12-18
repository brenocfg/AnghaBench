#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int status; int length; unsigned int dma; scalar_t__ zero; int /*<<< orphan*/  buf; } ;
struct ci13xxx_req {int map; TYPE_2__ req; int /*<<< orphan*/  dma; TYPE_5__* ptr; } ;
struct ci13xxx_ep {int dir; scalar_t__ type; int /*<<< orphan*/  num; TYPE_4__* qh; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int token; unsigned int* page; int /*<<< orphan*/  next; } ;
struct TYPE_9__ {TYPE_3__* ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  token; int /*<<< orphan*/  next; } ;
struct TYPE_8__ {int /*<<< orphan*/  cap; TYPE_1__ td; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EALREADY ; 
 int EBUSY ; 
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  QH_ZLT ; 
 int TD_IOC ; 
 unsigned int TD_RESERVED_MASK ; 
 int /*<<< orphan*/  TD_STATUS ; 
 int TD_STATUS_ACTIVE ; 
 int /*<<< orphan*/  TD_TERMINATE ; 
 int TD_TOTAL_BYTES ; 
 scalar_t__ USB_ENDPOINT_XFER_CONTROL ; 
 unsigned int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ffs_nr (int) ; 
 scalar_t__ hw_ep_is_primed (int /*<<< orphan*/ ,int) ; 
 int hw_ep_prime (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace (char*,struct ci13xxx_ep*,struct ci13xxx_req*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int _hardware_enqueue(struct ci13xxx_ep *mEp, struct ci13xxx_req *mReq)
{
	unsigned i;

	trace("%p, %p", mEp, mReq);

	/* don't queue twice */
	if (mReq->req.status == -EALREADY)
		return -EALREADY;

	if (hw_ep_is_primed(mEp->num, mEp->dir))
		return -EBUSY;

	mReq->req.status = -EALREADY;

	if (mReq->req.length && !mReq->req.dma) {
		mReq->req.dma = \
			dma_map_single(mEp->device, mReq->req.buf,
				       mReq->req.length, mEp->dir ?
				       DMA_TO_DEVICE : DMA_FROM_DEVICE);
		if (mReq->req.dma == 0)
			return -ENOMEM;

		mReq->map = 1;
	}

	/*
	 * TD configuration
	 * TODO - handle requests which spawns into several TDs
	 */
	memset(mReq->ptr, 0, sizeof(*mReq->ptr));
	mReq->ptr->next    |= TD_TERMINATE;
	mReq->ptr->token    = mReq->req.length << ffs_nr(TD_TOTAL_BYTES);
	mReq->ptr->token   &= TD_TOTAL_BYTES;
	mReq->ptr->token   |= TD_IOC;
	mReq->ptr->token   |= TD_STATUS_ACTIVE;
	mReq->ptr->page[0]  = mReq->req.dma;
	for (i = 1; i < 5; i++)
		mReq->ptr->page[i] =
			(mReq->req.dma + i * PAGE_SIZE) & ~TD_RESERVED_MASK;

	/*
	 *  QH configuration
	 *  At this point it's guaranteed exclusive access to qhead
	 *  (endpt is not primed) so it's no need to use tripwire
	 */
	mEp->qh[mEp->dir].ptr->td.next   = mReq->dma;    /* TERMINATE = 0 */
	mEp->qh[mEp->dir].ptr->td.token &= ~TD_STATUS;   /* clear status */
	if (mReq->req.zero == 0)
		mEp->qh[mEp->dir].ptr->cap |=  QH_ZLT;
	else
		mEp->qh[mEp->dir].ptr->cap &= ~QH_ZLT;

	wmb();   /* synchronize before ep prime */

	return hw_ep_prime(mEp->num, mEp->dir,
			   mEp->type == USB_ENDPOINT_XFER_CONTROL);
}