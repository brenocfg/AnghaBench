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
struct ucma_file {int /*<<< orphan*/  ctx_list; } ;
struct ucma_context {int /*<<< orphan*/  list; int /*<<< orphan*/  id; struct ucma_file* file; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctx_idr ; 
 int idr_get_new (int /*<<< orphan*/ *,struct ucma_context*,int /*<<< orphan*/ *) ; 
 int idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ucma_context*) ; 
 struct ucma_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ucma_context *ucma_alloc_ctx(struct ucma_file *file)
{
	struct ucma_context *ctx;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	atomic_set(&ctx->ref, 1);
	init_completion(&ctx->comp);
	INIT_LIST_HEAD(&ctx->mc_list);
	ctx->file = file;

	do {
		ret = idr_pre_get(&ctx_idr, GFP_KERNEL);
		if (!ret)
			goto error;

		mutex_lock(&mut);
		ret = idr_get_new(&ctx_idr, ctx, &ctx->id);
		mutex_unlock(&mut);
	} while (ret == -EAGAIN);

	if (ret)
		goto error;

	list_add_tail(&ctx->list, &file->ctx_list);
	return ctx;

error:
	kfree(ctx);
	return NULL;
}