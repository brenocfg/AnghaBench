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
struct TYPE_2__ {struct dma_buf* export_dma_buf; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct dma_buf {struct drm_i915_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (TYPE_1__*) ; 

__attribute__((used)) static void i915_gem_dmabuf_release(struct dma_buf *dma_buf)
{
	struct drm_i915_gem_object *obj = dma_buf->priv;

	if (obj->base.export_dma_buf == dma_buf) {
		/* drop the reference on the export fd holds */
		obj->base.export_dma_buf = NULL;
		drm_gem_object_unreference_unlocked(&obj->base);
	}
}