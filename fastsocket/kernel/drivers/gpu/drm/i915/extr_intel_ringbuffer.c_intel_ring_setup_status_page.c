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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ gfx_addr; } ;
struct intel_ring_buffer {int id; TYPE_1__ status_page; int /*<<< orphan*/  mmio_base; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;

/* Variables and functions */
#define  BCS 130 
 int /*<<< orphan*/  BLT_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  BSD_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
#define  RCS 129 
 int /*<<< orphan*/  RENDER_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  RING_HWS_PGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HWS_PGA_GEN6 (int /*<<< orphan*/ ) ; 
#define  VCS 128 

void intel_ring_setup_status_page(struct intel_ring_buffer *ring)
{
	struct drm_device *dev = ring->dev;
	drm_i915_private_t *dev_priv = ring->dev->dev_private;
	u32 mmio = 0;

	/* The ring status page addresses are no longer next to the rest of
	 * the ring registers as of gen7.
	 */
	if (IS_GEN7(dev)) {
		switch (ring->id) {
		case RCS:
			mmio = RENDER_HWS_PGA_GEN7;
			break;
		case BCS:
			mmio = BLT_HWS_PGA_GEN7;
			break;
		case VCS:
			mmio = BSD_HWS_PGA_GEN7;
			break;
		}
	} else if (IS_GEN6(ring->dev)) {
		mmio = RING_HWS_PGA_GEN6(ring->mmio_base);
	} else {
		mmio = RING_HWS_PGA(ring->mmio_base);
	}

	I915_WRITE(mmio, (u32)ring->status_page.gfx_addr);
	POSTING_READ(mmio);
}