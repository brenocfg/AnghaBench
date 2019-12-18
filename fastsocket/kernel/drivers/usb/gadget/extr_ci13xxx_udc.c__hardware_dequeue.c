#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; int length; int actual; scalar_t__ dma; } ;
struct ci13xxx_req {TYPE_2__ req; TYPE_1__* ptr; scalar_t__ map; } ;
struct ci13xxx_ep {scalar_t__ dir; int /*<<< orphan*/  device; int /*<<< orphan*/  num; } ;
struct TYPE_3__ {int token; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EALREADY ; 
 int ECONNRESET ; 
 int EINVAL ; 
 int TD_STATUS ; 
 int TD_STATUS_ACTIVE ; 
 int TD_STATUS_DT_ERR ; 
 int TD_STATUS_HALTED ; 
 int TD_STATUS_TR_ERR ; 
 int TD_TOTAL_BYTES ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int ffs_nr (int) ; 
 int /*<<< orphan*/  hw_ep_flush (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hw_ep_is_primed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,struct ci13xxx_ep*,struct ci13xxx_req*) ; 

__attribute__((used)) static int _hardware_dequeue(struct ci13xxx_ep *mEp, struct ci13xxx_req *mReq)
{
	trace("%p, %p", mEp, mReq);

	if (mReq->req.status != -EALREADY)
		return -EINVAL;

	if (hw_ep_is_primed(mEp->num, mEp->dir))
		hw_ep_flush(mEp->num, mEp->dir);

	mReq->req.status = 0;

	if (mReq->map) {
		dma_unmap_single(mEp->device, mReq->req.dma, mReq->req.length,
				 mEp->dir ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		mReq->req.dma = 0;
		mReq->map     = 0;
	}

	mReq->req.status = mReq->ptr->token & TD_STATUS;
	if      ((TD_STATUS_ACTIVE & mReq->req.status) != 0)
		mReq->req.status = -ECONNRESET;
	else if ((TD_STATUS_HALTED & mReq->req.status) != 0)
		mReq->req.status = -1;
	else if ((TD_STATUS_DT_ERR & mReq->req.status) != 0)
		mReq->req.status = -1;
	else if ((TD_STATUS_TR_ERR & mReq->req.status) != 0)
		mReq->req.status = -1;

	mReq->req.actual   = mReq->ptr->token & TD_TOTAL_BYTES;
	mReq->req.actual >>= ffs_nr(TD_TOTAL_BYTES);
	mReq->req.actual   = mReq->req.length - mReq->req.actual;
	mReq->req.actual   = mReq->req.status ? 0 : mReq->req.actual;

	return mReq->req.actual;
}