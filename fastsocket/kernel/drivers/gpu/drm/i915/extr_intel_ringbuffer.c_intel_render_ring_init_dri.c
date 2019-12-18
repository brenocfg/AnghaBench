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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_ring_buffer {char* name; size_t id; int size; int effective_size; int /*<<< orphan*/ * virtual_start; struct drm_device* dev; int /*<<< orphan*/  request_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  init; int /*<<< orphan*/  dispatch_execbuffer; int /*<<< orphan*/  write_tail; int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  irq_put; int /*<<< orphan*/  irq_get; int /*<<< orphan*/  set_seqno; int /*<<< orphan*/  get_seqno; int /*<<< orphan*/  flush; int /*<<< orphan*/  add_request; int /*<<< orphan*/  mmio_base; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_3__ {struct intel_ring_buffer* ring; } ;
typedef  TYPE_1__ drm_i915_private_t ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I915_NEED_GFX_HWS (struct drm_device*) ; 
 int /*<<< orphan*/  I915_USER_INTERRUPT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_845G (struct drm_device*) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_I830 (struct drm_device*) ; 
 size_t RCS ; 
 int /*<<< orphan*/  RENDER_RING_BASE ; 
 int /*<<< orphan*/  gen2_render_ring_flush ; 
 int /*<<< orphan*/  gen4_render_ring_flush ; 
 int /*<<< orphan*/  i830_dispatch_execbuffer ; 
 int /*<<< orphan*/  i8xx_ring_get_irq ; 
 int /*<<< orphan*/  i8xx_ring_put_irq ; 
 int /*<<< orphan*/  i915_dispatch_execbuffer ; 
 int /*<<< orphan*/  i965_dispatch_execbuffer ; 
 int /*<<< orphan*/  i9xx_add_request ; 
 int /*<<< orphan*/  i9xx_ring_get_irq ; 
 int /*<<< orphan*/  i9xx_ring_put_irq ; 
 int init_phys_hws_pga (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  init_render_ring ; 
 int /*<<< orphan*/ * ioremap_wc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  render_ring_cleanup ; 
 int /*<<< orphan*/  ring_get_seqno ; 
 int /*<<< orphan*/  ring_set_seqno ; 
 int /*<<< orphan*/  ring_write_tail ; 

int intel_render_ring_init_dri(struct drm_device *dev, u64 start, u32 size)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = &dev_priv->ring[RCS];
	int ret;

	ring->name = "render ring";
	ring->id = RCS;
	ring->mmio_base = RENDER_RING_BASE;

	if (INTEL_INFO(dev)->gen >= 6) {
		/* non-kms not supported on gen6+ */
		return -ENODEV;
	}

	/* Note: gem is not supported on gen5/ilk without kms (the corresponding
	 * gem_init ioctl returns with -ENODEV). Hence we do not need to set up
	 * the special gen5 functions. */
	ring->add_request = i9xx_add_request;
	if (INTEL_INFO(dev)->gen < 4)
		ring->flush = gen2_render_ring_flush;
	else
		ring->flush = gen4_render_ring_flush;
	ring->get_seqno = ring_get_seqno;
	ring->set_seqno = ring_set_seqno;
	if (IS_GEN2(dev)) {
		ring->irq_get = i8xx_ring_get_irq;
		ring->irq_put = i8xx_ring_put_irq;
	} else {
		ring->irq_get = i9xx_ring_get_irq;
		ring->irq_put = i9xx_ring_put_irq;
	}
	ring->irq_enable_mask = I915_USER_INTERRUPT;
	ring->write_tail = ring_write_tail;
	if (INTEL_INFO(dev)->gen >= 4)
		ring->dispatch_execbuffer = i965_dispatch_execbuffer;
	else if (IS_I830(dev) || IS_845G(dev))
		ring->dispatch_execbuffer = i830_dispatch_execbuffer;
	else
		ring->dispatch_execbuffer = i915_dispatch_execbuffer;
	ring->init = init_render_ring;
	ring->cleanup = render_ring_cleanup;

	ring->dev = dev;
	INIT_LIST_HEAD(&ring->active_list);
	INIT_LIST_HEAD(&ring->request_list);

	ring->size = size;
	ring->effective_size = ring->size;
	if (IS_I830(ring->dev) || IS_845G(ring->dev))
		ring->effective_size -= 128;

	ring->virtual_start = ioremap_wc(start, size);
	if (ring->virtual_start == NULL) {
		DRM_ERROR("can not ioremap virtual address for"
			  " ring buffer\n");
		return -ENOMEM;
	}

	if (!I915_NEED_GFX_HWS(dev)) {
		ret = init_phys_hws_pga(ring);
		if (ret)
			return ret;
	}

	return 0;
}