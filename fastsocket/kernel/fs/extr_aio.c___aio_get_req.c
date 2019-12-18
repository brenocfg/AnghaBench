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
struct TYPE_2__ {int /*<<< orphan*/ * ring_pages; } ;
struct kioctx {scalar_t__ reqs_active; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  active_reqs; TYPE_1__ ring_info; } ;
struct kiocb {int ki_users; int /*<<< orphan*/  ki_list; int /*<<< orphan*/ * ki_eventfd; int /*<<< orphan*/  ki_run_list; int /*<<< orphan*/ * ki_iovec; int /*<<< orphan*/ * private; int /*<<< orphan*/ * ki_dtor; int /*<<< orphan*/ * ki_retry; int /*<<< orphan*/ * ki_cancel; struct kioctx* ki_ctx; scalar_t__ ki_key; scalar_t__ ki_flags; } ;
struct aio_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ aio_ring_avail (TYPE_1__*,struct aio_ring*) ; 
 int /*<<< orphan*/  kiocb_cachep ; 
 struct aio_ring* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kiocb* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kiocb*) ; 
 int /*<<< orphan*/  kunmap_atomic (struct aio_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct kiocb *__aio_get_req(struct kioctx *ctx)
{
	struct kiocb *req = NULL;
	struct aio_ring *ring;
	int okay = 0;

	req = kmem_cache_alloc(kiocb_cachep, GFP_KERNEL);
	if (unlikely(!req))
		return NULL;

	req->ki_flags = 0;
	req->ki_users = 2;
	req->ki_key = 0;
	req->ki_ctx = ctx;
	req->ki_cancel = NULL;
	req->ki_retry = NULL;
	req->ki_dtor = NULL;
	req->private = NULL;
	req->ki_iovec = NULL;
	INIT_LIST_HEAD(&req->ki_run_list);
	req->ki_eventfd = NULL;

	/* Check if the completion queue has enough free space to
	 * accept an event from this io.
	 */
	spin_lock_irq(&ctx->ctx_lock);
	ring = kmap_atomic(ctx->ring_info.ring_pages[0], KM_USER0);
	if (ctx->reqs_active < aio_ring_avail(&ctx->ring_info, ring)) {
		list_add(&req->ki_list, &ctx->active_reqs);
		ctx->reqs_active++;
		okay = 1;
	}
	kunmap_atomic(ring, KM_USER0);
	spin_unlock_irq(&ctx->ctx_lock);

	if (!okay) {
		kmem_cache_free(kiocb_cachep, req);
		req = NULL;
	}

	return req;
}