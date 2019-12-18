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
struct intel_ring_buffer {char* name; size_t id; int /*<<< orphan*/  init; int /*<<< orphan*/ * signal_mbox; int /*<<< orphan*/ * semaphore_register; int /*<<< orphan*/  sync_to; int /*<<< orphan*/  dispatch_execbuffer; int /*<<< orphan*/  irq_put; int /*<<< orphan*/  irq_get; int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  set_seqno; int /*<<< orphan*/  get_seqno; int /*<<< orphan*/  add_request; int /*<<< orphan*/  flush; int /*<<< orphan*/  write_tail; int /*<<< orphan*/  mmio_base; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {struct intel_ring_buffer* ring; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 size_t BCS ; 
 int /*<<< orphan*/  BLT_RING_BASE ; 
 int /*<<< orphan*/  GEN6_BLITTER_USER_INTERRUPT ; 
 int /*<<< orphan*/  GEN6_RBSYNC ; 
 int /*<<< orphan*/  GEN6_VBSYNC ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_BR ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_BV ; 
 int /*<<< orphan*/  MI_SEMAPHORE_SYNC_INVALID ; 
 int /*<<< orphan*/  blt_ring_flush ; 
 int /*<<< orphan*/  gen6_add_request ; 
 int /*<<< orphan*/  gen6_ring_dispatch_execbuffer ; 
 int /*<<< orphan*/  gen6_ring_get_irq ; 
 int /*<<< orphan*/  gen6_ring_get_seqno ; 
 int /*<<< orphan*/  gen6_ring_put_irq ; 
 int /*<<< orphan*/  gen6_ring_sync ; 
 int /*<<< orphan*/  init_ring_common ; 
 int intel_init_ring_buffer (struct drm_device*,struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  ring_set_seqno ; 
 int /*<<< orphan*/  ring_write_tail ; 

int intel_init_blt_ring_buffer(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = &dev_priv->ring[BCS];

	ring->name = "blitter ring";
	ring->id = BCS;

	ring->mmio_base = BLT_RING_BASE;
	ring->write_tail = ring_write_tail;
	ring->flush = blt_ring_flush;
	ring->add_request = gen6_add_request;
	ring->get_seqno = gen6_ring_get_seqno;
	ring->set_seqno = ring_set_seqno;
	ring->irq_enable_mask = GEN6_BLITTER_USER_INTERRUPT;
	ring->irq_get = gen6_ring_get_irq;
	ring->irq_put = gen6_ring_put_irq;
	ring->dispatch_execbuffer = gen6_ring_dispatch_execbuffer;
	ring->sync_to = gen6_ring_sync;
	ring->semaphore_register[0] = MI_SEMAPHORE_SYNC_BR;
	ring->semaphore_register[1] = MI_SEMAPHORE_SYNC_BV;
	ring->semaphore_register[2] = MI_SEMAPHORE_SYNC_INVALID;
	ring->signal_mbox[0] = GEN6_RBSYNC;
	ring->signal_mbox[1] = GEN6_VBSYNC;
	ring->init = init_ring_common;

	return intel_init_ring_buffer(dev, ring);
}