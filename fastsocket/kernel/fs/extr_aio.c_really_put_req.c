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
struct kioctx {int /*<<< orphan*/  wait; scalar_t__ dead; int /*<<< orphan*/  reqs_active; int /*<<< orphan*/  ctx_lock; } ;
struct kiocb {int /*<<< orphan*/ * ki_iovec; int /*<<< orphan*/  ki_inline_vec; int /*<<< orphan*/  (* ki_dtor ) (struct kiocb*) ;int /*<<< orphan*/ * ki_eventfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eventfd_ctx_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kiocb_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kiocb*) ; 
 int /*<<< orphan*/  stub1 (struct kiocb*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void really_put_req(struct kioctx *ctx, struct kiocb *req)
{
	assert_spin_locked(&ctx->ctx_lock);

	if (req->ki_eventfd != NULL)
		eventfd_ctx_put(req->ki_eventfd);
	if (req->ki_dtor)
		req->ki_dtor(req);
	if (req->ki_iovec != &req->ki_inline_vec)
		kfree(req->ki_iovec);
	kmem_cache_free(kiocb_cachep, req);
	ctx->reqs_active--;

	if (unlikely(!ctx->reqs_active && ctx->dead))
		wake_up(&ctx->wait);
}