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
struct pipe_control {struct drm_i915_gem_object* obj; int /*<<< orphan*/  gtt_offset; int /*<<< orphan*/ * cpu_page; } ;
struct intel_ring_buffer {struct pipe_control* private; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; TYPE_1__* pages; int /*<<< orphan*/  gtt_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* i915_gem_alloc_object (int /*<<< orphan*/ ,int) ; 
 int i915_gem_object_pin (struct drm_i915_gem_object*,int,int,int) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_level (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct pipe_control*) ; 
 struct pipe_control* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_pipe_control(struct intel_ring_buffer *ring)
{
	struct pipe_control *pc;
	struct drm_i915_gem_object *obj;
	int ret;

	if (ring->private)
		return 0;

	pc = kmalloc(sizeof(*pc), GFP_KERNEL);
	if (!pc)
		return -ENOMEM;

	obj = i915_gem_alloc_object(ring->dev, 4096);
	if (obj == NULL) {
		DRM_ERROR("Failed to allocate seqno page\n");
		ret = -ENOMEM;
		goto err;
	}

	i915_gem_object_set_cache_level(obj, I915_CACHE_LLC);

	ret = i915_gem_object_pin(obj, 4096, true, false);
	if (ret)
		goto err_unref;

	pc->gtt_offset = obj->gtt_offset;
	pc->cpu_page =  kmap(sg_page(obj->pages->sgl));
	if (pc->cpu_page == NULL)
		goto err_unpin;

	DRM_DEBUG_DRIVER("%s pipe control offset: 0x%08x\n",
			 ring->name, pc->gtt_offset);

	pc->obj = obj;
	ring->private = pc;
	return 0;

err_unpin:
	i915_gem_object_unpin(obj);
err_unref:
	drm_gem_object_unreference(&obj->base);
err:
	kfree(pc);
	return ret;
}