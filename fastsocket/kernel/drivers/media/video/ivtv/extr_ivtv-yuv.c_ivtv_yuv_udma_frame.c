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
struct ivtv_dma_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ivtv {TYPE_1__ udma; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA_PENDING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_udma_prepare (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_udma_unmap (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_yuv_frame_complete (struct ivtv*) ; 
 int ivtv_yuv_prep_user_dma (struct ivtv*,TYPE_1__*,struct ivtv_dma_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int ivtv_yuv_udma_frame(struct ivtv *itv, struct ivtv_dma_frame *args)
{
	DEFINE_WAIT(wait);
	int rc = 0;
	int got_sig = 0;
	/* DMA the frame */
	mutex_lock(&itv->udma.lock);

	if ((rc = ivtv_yuv_prep_user_dma(itv, &itv->udma, args)) != 0) {
		mutex_unlock(&itv->udma.lock);
		return rc;
	}

	ivtv_udma_prepare(itv);
	prepare_to_wait(&itv->dma_waitq, &wait, TASK_INTERRUPTIBLE);
	/* if no UDMA is pending and no UDMA is in progress, then the DMA
	   is finished */
	while (test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags) ||
	       test_bit(IVTV_F_I_UDMA, &itv->i_flags)) {
		/* don't interrupt if the DMA is in progress but break off
		   a still pending DMA. */
		got_sig = signal_pending(current);
		if (got_sig && test_and_clear_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags))
			break;
		got_sig = 0;
		schedule();
	}
	finish_wait(&itv->dma_waitq, &wait);

	/* Unmap Last DMA Xfer */
	ivtv_udma_unmap(itv);

	if (got_sig) {
		IVTV_DEBUG_INFO("User stopped YUV UDMA\n");
		mutex_unlock(&itv->udma.lock);
		return -EINTR;
	}

	ivtv_yuv_frame_complete(itv);

	mutex_unlock(&itv->udma.lock);
	return rc;
}