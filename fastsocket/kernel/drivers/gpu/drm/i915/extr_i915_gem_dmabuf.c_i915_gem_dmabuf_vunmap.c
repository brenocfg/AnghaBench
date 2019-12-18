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
struct TYPE_2__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {scalar_t__ vmapping_count; int /*<<< orphan*/ * dma_buf_vmapping; TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct dma_buf {struct drm_i915_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_gem_dmabuf_vunmap(struct dma_buf *dma_buf, void *vaddr)
{
	struct drm_i915_gem_object *obj = dma_buf->priv;
	struct drm_device *dev = obj->base.dev;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return;

	if (--obj->vmapping_count == 0) {
		vunmap(obj->dma_buf_vmapping);
		obj->dma_buf_vmapping = NULL;

		i915_gem_object_unpin_pages(obj);
	}
	mutex_unlock(&dev->struct_mutex);
}