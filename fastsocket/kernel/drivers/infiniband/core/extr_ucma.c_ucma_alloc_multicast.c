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
struct ucma_multicast {int /*<<< orphan*/  list; struct ucma_context* ctx; int /*<<< orphan*/  id; } ;
struct ucma_context {int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_get_new (int /*<<< orphan*/ *,struct ucma_multicast*,int /*<<< orphan*/ *) ; 
 int idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ucma_multicast*) ; 
 struct ucma_multicast* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multicast_idr ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ucma_multicast* ucma_alloc_multicast(struct ucma_context *ctx)
{
	struct ucma_multicast *mc;
	int ret;

	mc = kzalloc(sizeof(*mc), GFP_KERNEL);
	if (!mc)
		return NULL;

	do {
		ret = idr_pre_get(&multicast_idr, GFP_KERNEL);
		if (!ret)
			goto error;

		mutex_lock(&mut);
		ret = idr_get_new(&multicast_idr, mc, &mc->id);
		mutex_unlock(&mut);
	} while (ret == -EAGAIN);

	if (ret)
		goto error;

	mc->ctx = ctx;
	list_add_tail(&mc->list, &ctx->mc_list);
	return mc;

error:
	kfree(mc);
	return NULL;
}