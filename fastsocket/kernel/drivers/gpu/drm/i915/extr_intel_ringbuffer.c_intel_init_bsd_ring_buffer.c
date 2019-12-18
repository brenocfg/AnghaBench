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
struct intel_ring_buffer {char* name; size_t id; int /*<<< orphan*/  init; int /*<<< orphan*/  dispatch_execbuffer; int /*<<< orphan*/  irq_put; int /*<<< orphan*/  irq_get; int /*<<< orphan*/  irq_enable_mask; void* set_seqno; int /*<<< orphan*/  get_seqno; int /*<<< orphan*/  add_request; int /*<<< orphan*/  flush; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/ * signal_mbox; int /*<<< orphan*/ * semaphore_register; int /*<<< orphan*/  sync_to; int /*<<< orphan*/  write_tail; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {struct intel_ring_buffer* ring; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_RING_BASE ; 
 int /*<<< orphan*/  GEN6_BSD_RING_BASE ; 
 int /*<<< orphan*/  GEN6_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  GEN6_BVSYNC ; 
 int /*<<< orphan*/  GEN6_RVSYNC ; 
 int /*<<< orphan*/  GT_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  I915_BSD_USER_INTERRUPT ; 
 scalar_t__ IS_GEN5 (struct drm_device*) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_INVALID ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_VB ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_VR ; 
 size_t VCS ; 
 int /*<<< orphan*/  bsd_ring_flush ; 
 int /*<<< orphan*/  gen5_ring_get_irq ; 
 int /*<<< orphan*/  gen5_ring_put_irq ; 
 int /*<<< orphan*/  gen6_add_request ; 
 int /*<<< orphan*/  gen6_bsd_ring_write_tail ; 
 int /*<<< orphan*/  gen6_ring_dispatch_execbuffer ; 
 int /*<<< orphan*/  gen6_ring_flush ; 
 int /*<<< orphan*/  gen6_ring_get_irq ; 
 int /*<<< orphan*/  gen6_ring_get_seqno ; 
 int /*<<< orphan*/  gen6_ring_put_irq ; 
 int /*<<< orphan*/  gen6_ring_sync ; 
 int /*<<< orphan*/  i965_dispatch_execbuffer ; 
 int /*<<< orphan*/  i9xx_add_request ; 
 int /*<<< orphan*/  i9xx_ring_get_irq ; 
 int /*<<< orphan*/  i9xx_ring_put_irq ; 
 int /*<<< orphan*/  init_ring_common ; 
 int intel_init_ring_buffer (struct drm_device*,struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  ring_get_seqno ; 
 void* ring_set_seqno ; 
 int /*<<< orphan*/  ring_write_tail ; 

int intel_init_bsd_ring_buffer(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = &dev_priv->ring[VCS];

	ring->name = "bsd ring";
	ring->id = VCS;

	ring->write_tail = ring_write_tail;
	if (IS_GEN6(dev) || IS_GEN7(dev)) {
		ring->mmio_base = GEN6_BSD_RING_BASE;
		/* gen6 bsd needs a special wa for tail updates */
		if (IS_GEN6(dev))
			ring->write_tail = gen6_bsd_ring_write_tail;
		ring->flush = gen6_ring_flush;
		ring->add_request = gen6_add_request;
		ring->get_seqno = gen6_ring_get_seqno;
		ring->set_seqno = ring_set_seqno;
		ring->irq_enable_mask = GEN6_BSD_USER_INTERRUPT;
		ring->irq_get = gen6_ring_get_irq;
		ring->irq_put = gen6_ring_put_irq;
		ring->dispatch_execbuffer = gen6_ring_dispatch_execbuffer;
		ring->sync_to = gen6_ring_sync;
		ring->semaphore_register[0] = MI_SEMAPHORE_SYNC_VR;
		ring->semaphore_register[1] = MI_SEMAPHORE_SYNC_INVALID;
		ring->semaphore_register[2] = MI_SEMAPHORE_SYNC_VB;
		ring->signal_mbox[0] = GEN6_RVSYNC;
		ring->signal_mbox[1] = GEN6_BVSYNC;
	} else {
		ring->mmio_base = BSD_RING_BASE;
		ring->flush = bsd_ring_flush;
		ring->add_request = i9xx_add_request;
		ring->get_seqno = ring_get_seqno;
		ring->set_seqno = ring_set_seqno;
		if (IS_GEN5(dev)) {
			ring->irq_enable_mask = GT_BSD_USER_INTERRUPT;
			ring->irq_get = gen5_ring_get_irq;
			ring->irq_put = gen5_ring_put_irq;
		} else {
			ring->irq_enable_mask = I915_BSD_USER_INTERRUPT;
			ring->irq_get = i9xx_ring_get_irq;
			ring->irq_put = i9xx_ring_put_irq;
		}
		ring->dispatch_execbuffer = i965_dispatch_execbuffer;
	}
	ring->init = init_ring_common;

	return intel_init_ring_buffer(dev, ring);
}