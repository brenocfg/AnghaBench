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
struct TYPE_2__ {int /*<<< orphan*/  import_attach; } ;
struct drm_i915_gem_object {int has_dma_mapping; int /*<<< orphan*/  pages; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_gem_object_put_pages_dmabuf(struct drm_i915_gem_object *obj)
{
	dma_buf_unmap_attachment(obj->base.import_attach,
				 obj->pages, DMA_BIDIRECTIONAL);
	obj->has_dma_mapping = false;
}