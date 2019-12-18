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
struct drm_gem_object {struct dma_buf_attachment* import_attach; struct drm_device* dev; } ;
struct drm_i915_gem_object {struct drm_gem_object base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf_attachment {int dummy; } ;
struct dma_buf {int /*<<< orphan*/  size; struct drm_i915_gem_object* priv; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_CAST (struct dma_buf_attachment*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dma_buf_attachment*) ; 
 struct dma_buf_attachment* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  drm_gem_object_reference (struct drm_gem_object*) ; 
 int drm_gem_private_object_init (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 int /*<<< orphan*/  i915_dmabuf_ops ; 
 struct drm_i915_gem_object* i915_gem_object_alloc (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_object_dmabuf_ops ; 
 int /*<<< orphan*/  i915_gem_object_free (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 

struct drm_gem_object *i915_gem_prime_import(struct drm_device *dev,
					     struct dma_buf *dma_buf)
{
	struct dma_buf_attachment *attach;
	struct drm_i915_gem_object *obj;
	int ret;

	/* is this one of own objects? */
	if (dma_buf->ops == &i915_dmabuf_ops) {
		obj = dma_buf->priv;
		/* is it from our device? */
		if (obj->base.dev == dev) {
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_reference(&obj->base);
			return &obj->base;
		}
	}

	/* need to attach */
	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_ERR(attach))
		return ERR_CAST(attach);

	get_dma_buf(dma_buf);

	obj = i915_gem_object_alloc(dev);
	if (obj == NULL) {
		ret = -ENOMEM;
		goto fail_detach;
	}

	ret = drm_gem_private_object_init(dev, &obj->base, dma_buf->size);
	if (ret) {
		i915_gem_object_free(obj);
		goto fail_detach;
	}

	i915_gem_object_init(obj, &i915_gem_object_dmabuf_ops);
	obj->base.import_attach = attach;

	return &obj->base;

fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	return ERR_PTR(ret);
}