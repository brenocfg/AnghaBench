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
struct i915_hw_context {int /*<<< orphan*/  obj; } ;
struct drm_i915_private {TYPE_1__* ring; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_3__ {struct i915_hw_context* default_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONTEXT_ALIGN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ IS_ERR (struct i915_hw_context*) ; 
 int PTR_ERR (struct i915_hw_context*) ; 
 size_t RCS ; 
 struct i915_hw_context* create_hw_context (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_destroy (struct i915_hw_context*) ; 
 int do_switch (struct i915_hw_context*) ; 
 int i915_gem_object_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_default_context(struct drm_i915_private *dev_priv)
{
	struct i915_hw_context *ctx;
	int ret;

	BUG_ON(!mutex_is_locked(&dev_priv->dev->struct_mutex));

	ctx = create_hw_context(dev_priv->dev, NULL);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	/* We may need to do things with the shrinker which require us to
	 * immediately switch back to the default context. This can cause a
	 * problem as pinning the default context also requires GTT space which
	 * may not be available. To avoid this we always pin the
	 * default context.
	 */
	dev_priv->ring[RCS].default_context = ctx;
	ret = i915_gem_object_pin(ctx->obj, CONTEXT_ALIGN, false, false);
	if (ret)
		goto err_destroy;

	ret = do_switch(ctx);
	if (ret)
		goto err_unpin;

	DRM_DEBUG_DRIVER("Default HW context loaded\n");
	return 0;

err_unpin:
	i915_gem_object_unpin(ctx->obj);
err_destroy:
	do_destroy(ctx);
	return ret;
}