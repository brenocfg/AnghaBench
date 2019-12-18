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
struct i915_hw_context {TYPE_2__* obj; int /*<<< orphan*/  id; TYPE_1__* file_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  context_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i915_hw_context*) ; 

__attribute__((used)) static void do_destroy(struct i915_hw_context *ctx)
{
	if (ctx->file_priv)
		idr_remove(&ctx->file_priv->context_idr, ctx->id);

	drm_gem_object_unreference(&ctx->obj->base);
	kfree(ctx);
}