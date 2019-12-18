#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ gfx_addr; } ;
struct intel_ring_buffer {TYPE_2__ status_page; } ;
struct drm_device {TYPE_3__* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  gfx_hws_cpu_addr; } ;
struct TYPE_7__ {TYPE_1__ dri1; int /*<<< orphan*/ * status_page_dmah; } ;
typedef  TYPE_3__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  HWS_PGA ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct intel_ring_buffer* LP_RING (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_pci_free (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_free_hws(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	if (dev_priv->status_page_dmah) {
		drm_pci_free(dev, dev_priv->status_page_dmah);
		dev_priv->status_page_dmah = NULL;
	}

	if (ring->status_page.gfx_addr) {
		ring->status_page.gfx_addr = 0;
		iounmap(dev_priv->dri1.gfx_hws_cpu_addr);
	}

	/* Need to rewrite hardware status page */
	I915_WRITE(HWS_PGA, 0x1ffff000);
}