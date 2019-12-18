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
struct i915_hw_context {int id; struct drm_i915_file_private* file_priv; int /*<<< orphan*/ * ring; int /*<<< orphan*/ * obj; } ;
struct drm_i915_private {int /*<<< orphan*/ * ring; int /*<<< orphan*/  hw_context_size; } ;
struct drm_i915_file_private {int /*<<< orphan*/  context_idr; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_CONTEXT_ID ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 struct i915_hw_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_CACHE_LLC_MLC ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 size_t RCS ; 
 int /*<<< orphan*/  do_destroy (struct i915_hw_context*) ; 
 int /*<<< orphan*/ * i915_gem_alloc_object (struct drm_device*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_cache_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct i915_hw_context*,scalar_t__,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i915_hw_context*) ; 
 struct i915_hw_context* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_hw_context *
create_hw_context(struct drm_device *dev,
		  struct drm_i915_file_private *file_priv)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_hw_context *ctx;
	int ret, id;

	ctx = kzalloc(sizeof(struct drm_i915_file_private), GFP_KERNEL);
	if (ctx == NULL)
		return ERR_PTR(-ENOMEM);

	ctx->obj = i915_gem_alloc_object(dev, dev_priv->hw_context_size);
	if (ctx->obj == NULL) {
		kfree(ctx);
		DRM_DEBUG_DRIVER("Context object allocated failed\n");
		return ERR_PTR(-ENOMEM);
	}

	if (INTEL_INFO(dev)->gen >= 7) {
		ret = i915_gem_object_set_cache_level(ctx->obj,
						      I915_CACHE_LLC_MLC);
		if (ret)
			goto err_out;
	}

	/* The ring associated with the context object is handled by the normal
	 * object tracking code. We give an initial ring value simple to pass an
	 * assertion in the context switch code.
	 */
	ctx->ring = &dev_priv->ring[RCS];

	/* Default context will never have a file_priv */
	if (file_priv == NULL)
		return ctx;

	ctx->file_priv = file_priv;

again:
	if (idr_pre_get(&file_priv->context_idr, GFP_KERNEL) == 0) {
		ret = -ENOMEM;
		DRM_DEBUG_DRIVER("idr allocation failed\n");
		goto err_out;
	}

	ret = idr_get_new_above(&file_priv->context_idr, ctx,
				DEFAULT_CONTEXT_ID + 1, &id);
	if (ret == 0)
		ctx->id = id;

	if (ret == -EAGAIN)
		goto again;
	else if (ret)
		goto err_out;

	return ctx;

err_out:
	do_destroy(ctx);
	return ERR_PTR(ret);
}