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
struct mm_struct {int /*<<< orphan*/  ioctx_lock; int /*<<< orphan*/  ioctx_list; int /*<<< orphan*/  mm_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; int /*<<< orphan*/  ring_lock; } ;
struct kioctx {unsigned int max_reqs; TYPE_1__ ring_info; int /*<<< orphan*/  user_id; int /*<<< orphan*/  list; int /*<<< orphan*/  wq; int /*<<< orphan*/  run_list; int /*<<< orphan*/  active_reqs; int /*<<< orphan*/  wait; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  users; struct mm_struct* mm; } ;
struct kiocb {int dummy; } ;
struct io_event {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct kioctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __put_ioctx (struct kioctx*) ; 
 int /*<<< orphan*/  aio_kick_handler ; 
 unsigned long aio_max_nr ; 
 unsigned int aio_nr ; 
 int /*<<< orphan*/  aio_nr_lock ; 
 scalar_t__ aio_setup_ring (struct kioctx*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dprintk (char*,struct kioctx*,...) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kioctx_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kioctx*) ; 
 struct kioctx* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static struct kioctx *ioctx_alloc(unsigned nr_events)
{
	struct mm_struct *mm;
	struct kioctx *ctx;
	int did_sync = 0;

	/* Prevent overflows */
	if ((nr_events > (0x10000000U / sizeof(struct io_event))) ||
	    (nr_events > (0x10000000U / sizeof(struct kiocb)))) {
		pr_debug("ENOMEM: nr_events too high\n");
		return ERR_PTR(-EINVAL);
	}

	if ((unsigned long)nr_events > aio_max_nr)
		return ERR_PTR(-EAGAIN);

	ctx = kmem_cache_zalloc(kioctx_cachep, GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	ctx->max_reqs = nr_events;
	mm = ctx->mm = current->mm;
	atomic_inc(&mm->mm_count);

	atomic_set(&ctx->users, 2);
	spin_lock_init(&ctx->ctx_lock);
	spin_lock_init(&ctx->ring_info.ring_lock);
	init_waitqueue_head(&ctx->wait);

	INIT_LIST_HEAD(&ctx->active_reqs);
	INIT_LIST_HEAD(&ctx->run_list);
	INIT_DELAYED_WORK(&ctx->wq, aio_kick_handler);

	if (aio_setup_ring(ctx) < 0)
		goto out_freectx;

	/* limit the number of system wide aios */
	do {
		spin_lock_bh(&aio_nr_lock);
		if (aio_nr + nr_events > aio_max_nr ||
		    aio_nr + nr_events < aio_nr)
			ctx->max_reqs = 0;
		else
			aio_nr += ctx->max_reqs;
		spin_unlock_bh(&aio_nr_lock);
		if (ctx->max_reqs || did_sync)
			break;

		/* wait for rcu callbacks to have completed before giving up */
		synchronize_rcu();
		did_sync = 1;
		ctx->max_reqs = nr_events;
	} while (1);

	if (ctx->max_reqs == 0)
		goto out_cleanup;

	/* now link into global list. */
	spin_lock(&mm->ioctx_lock);
	hlist_add_head_rcu(&ctx->list, &mm->ioctx_list);
	spin_unlock(&mm->ioctx_lock);

	dprintk("aio: allocated ioctx %p[%ld]: mm=%p mask=0x%x\n",
		ctx, ctx->user_id, current->mm, ctx->ring_info.nr);
	return ctx;

out_cleanup:
	__put_ioctx(ctx);
	return ERR_PTR(-EAGAIN);

out_freectx:
	mmdrop(mm);
	kmem_cache_free(kioctx_cachep, ctx);
	ctx = ERR_PTR(-ENOMEM);

	dprintk("aio: error allocating ioctx %p\n", ctx);
	return ctx;
}