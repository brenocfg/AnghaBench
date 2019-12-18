#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct aio_ring_info {unsigned long tail; unsigned long nr; int /*<<< orphan*/ * ring_pages; } ;
struct kioctx {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  wait; struct aio_ring_info ring_info; } ;
struct TYPE_4__ {scalar_t__ user; int /*<<< orphan*/  tsk; } ;
struct TYPE_5__ {scalar_t__ prev; } ;
struct kiocb {int ki_users; long ki_user_data; int /*<<< orphan*/ * ki_eventfd; TYPE_1__ ki_obj; TYPE_2__ ki_run_list; struct kioctx* ki_ctx; } ;
struct io_event {long data; long res; long res2; scalar_t__ obj; } ;
struct aio_ring {unsigned long tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KM_IRQ0 ; 
 int /*<<< orphan*/  KM_IRQ1 ; 
 int __aio_put_req (struct kioctx*,struct kiocb*) ; 
 struct io_event* aio_ring_event (struct aio_ring_info*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,struct kioctx*,unsigned long,struct kiocb*,scalar_t__,long,long,long) ; 
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ kiocbIsCancelled (struct kiocb*) ; 
 struct aio_ring* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct aio_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (TYPE_2__*) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct kiocb*,unsigned long) ; 
 int /*<<< orphan*/  put_aio_ring_event (struct io_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int aio_complete(struct kiocb *iocb, long res, long res2)
{
	struct kioctx	*ctx = iocb->ki_ctx;
	struct aio_ring_info	*info;
	struct aio_ring	*ring;
	struct io_event	*event;
	unsigned long	flags;
	unsigned long	tail;
	int		ret;

	/*
	 * Special case handling for sync iocbs:
	 *  - events go directly into the iocb for fast handling
	 *  - the sync task with the iocb in its stack holds the single iocb
	 *    ref, no other paths have a way to get another ref
	 *  - the sync task helpfully left a reference to itself in the iocb
	 */
	if (is_sync_kiocb(iocb)) {
		BUG_ON(iocb->ki_users != 1);
		iocb->ki_user_data = res;
		iocb->ki_users = 0;
		wake_up_process(iocb->ki_obj.tsk);
		return 1;
	}

	info = &ctx->ring_info;

	/* add a completion event to the ring buffer.
	 * must be done holding ctx->ctx_lock to prevent
	 * other code from messing with the tail
	 * pointer since we might be called from irq
	 * context.
	 */
	spin_lock_irqsave(&ctx->ctx_lock, flags);

	if (iocb->ki_run_list.prev && !list_empty(&iocb->ki_run_list))
		list_del_init(&iocb->ki_run_list);

	/*
	 * cancelled requests don't get events, userland was given one
	 * when the event got cancelled.
	 */
	if (kiocbIsCancelled(iocb))
		goto put_rq;

	ring = kmap_atomic(info->ring_pages[0], KM_IRQ1);

	tail = info->tail;
	event = aio_ring_event(info, tail, KM_IRQ0);
	if (++tail >= info->nr)
		tail = 0;

	event->obj = (u64)(unsigned long)iocb->ki_obj.user;
	event->data = iocb->ki_user_data;
	event->res = res;
	event->res2 = res2;

	dprintk("aio_complete: %p[%lu]: %p: %p %Lx %lx %lx\n",
		ctx, tail, iocb, iocb->ki_obj.user, iocb->ki_user_data,
		res, res2);

	/* after flagging the request as done, we
	 * must never even look at it again
	 */
	smp_wmb();	/* make event visible before updating tail */

	info->tail = tail;
	ring->tail = tail;

	put_aio_ring_event(event, KM_IRQ0);
	kunmap_atomic(ring, KM_IRQ1);

	pr_debug("added to ring %p at [%lu]\n", iocb, tail);

	/*
	 * Check if the user asked us to deliver the result through an
	 * eventfd. The eventfd_signal() function is safe to be called
	 * from IRQ context.
	 */
	if (iocb->ki_eventfd != NULL)
		eventfd_signal(iocb->ki_eventfd, 1);

put_rq:
	/* everything turned out well, dispose of the aiocb. */
	ret = __aio_put_req(ctx, iocb);

	/*
	 * We have to order our ring_info tail store above and test
	 * of the wait list below outside the wait lock.  This is
	 * like in wake_up_bit() where clearing a bit has to be
	 * ordered with the unlocked test.
	 */
	smp_mb();

	if (waitqueue_active(&ctx->wait))
		wake_up(&ctx->wait);

	spin_unlock_irqrestore(&ctx->ctx_lock, flags);
	return ret;
}