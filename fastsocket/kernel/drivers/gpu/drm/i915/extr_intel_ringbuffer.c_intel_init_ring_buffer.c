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
struct intel_ring_buffer {int size; scalar_t__ id; int (* init ) (struct intel_ring_buffer*) ;int effective_size; struct drm_i915_gem_object* obj; int /*<<< orphan*/ * virtual_start; struct drm_device* dev; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  sync_seqno; int /*<<< orphan*/  request_list; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {scalar_t__ mappable_base; } ;
struct drm_i915_private {TYPE_1__ gtt; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; scalar_t__ gtt_offset; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_device*) ; 
 scalar_t__ I915_NEED_GFX_HWS (struct drm_device*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_845G (struct drm_device*) ; 
 scalar_t__ IS_I830 (struct drm_device*) ; 
 int PAGE_SIZE ; 
 scalar_t__ RCS ; 
 int /*<<< orphan*/  cleanup_status_page (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* i915_gem_alloc_object (struct drm_device*,int) ; 
 struct drm_i915_gem_object* i915_gem_object_create_stolen (struct drm_device*,int) ; 
 int i915_gem_object_pin (struct drm_i915_gem_object*,int,int,int) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 int init_phys_hws_pga (struct intel_ring_buffer*) ; 
 int init_status_page (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ioremap_wc (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct intel_ring_buffer*) ; 

__attribute__((used)) static int intel_init_ring_buffer(struct drm_device *dev,
				  struct intel_ring_buffer *ring)
{
	struct drm_i915_gem_object *obj;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ring->dev = dev;
	INIT_LIST_HEAD(&ring->active_list);
	INIT_LIST_HEAD(&ring->request_list);
	ring->size = 32 * PAGE_SIZE;
	memset(ring->sync_seqno, 0, sizeof(ring->sync_seqno));

	init_waitqueue_head(&ring->irq_queue);

	if (I915_NEED_GFX_HWS(dev)) {
		ret = init_status_page(ring);
		if (ret)
			return ret;
	} else {
		BUG_ON(ring->id != RCS);
		ret = init_phys_hws_pga(ring);
		if (ret)
			return ret;
	}

	obj = NULL;
	if (!HAS_LLC(dev))
		obj = i915_gem_object_create_stolen(dev, ring->size);
	if (obj == NULL)
		obj = i915_gem_alloc_object(dev, ring->size);
	if (obj == NULL) {
		DRM_ERROR("Failed to allocate ringbuffer\n");
		ret = -ENOMEM;
		goto err_hws;
	}

	ring->obj = obj;

	ret = i915_gem_object_pin(obj, PAGE_SIZE, true, false);
	if (ret)
		goto err_unref;

	ret = i915_gem_object_set_to_gtt_domain(obj, true);
	if (ret)
		goto err_unpin;

	ring->virtual_start =
		ioremap_wc(dev_priv->gtt.mappable_base + obj->gtt_offset,
			   ring->size);
	if (ring->virtual_start == NULL) {
		DRM_ERROR("Failed to map ringbuffer.\n");
		ret = -EINVAL;
		goto err_unpin;
	}

	ret = ring->init(ring);
	if (ret)
		goto err_unmap;

	/* Workaround an erratum on the i830 which causes a hang if
	 * the TAIL pointer points to within the last 2 cachelines
	 * of the buffer.
	 */
	ring->effective_size = ring->size;
	if (IS_I830(ring->dev) || IS_845G(ring->dev))
		ring->effective_size -= 128;

	return 0;

err_unmap:
	iounmap(ring->virtual_start);
err_unpin:
	i915_gem_object_unpin(obj);
err_unref:
	drm_gem_object_unreference(&obj->base);
	ring->obj = NULL;
err_hws:
	cleanup_status_page(ring);
	return ret;
}