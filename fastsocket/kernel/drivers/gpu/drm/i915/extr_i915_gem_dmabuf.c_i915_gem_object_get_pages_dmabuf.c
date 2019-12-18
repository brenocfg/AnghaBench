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
struct sg_table {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  import_attach; } ;
struct drm_i915_gem_object {int has_dma_mapping; struct sg_table* pages; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 struct sg_table* dma_buf_map_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_object_get_pages_dmabuf(struct drm_i915_gem_object *obj)
{
	struct sg_table *sg;

	sg = dma_buf_map_attachment(obj->base.import_attach, DMA_BIDIRECTIONAL);
	if (IS_ERR(sg))
		return PTR_ERR(sg);

	obj->pages = sg;
	obj->has_dma_mapping = true;
	return 0;
}