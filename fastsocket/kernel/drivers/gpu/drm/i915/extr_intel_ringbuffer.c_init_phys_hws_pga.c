#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  page_addr; } ;
struct intel_ring_buffer {TYPE_1__ status_page; TYPE_3__* dev; } ;
struct drm_i915_private {TYPE_2__* status_page_dmah; } ;
struct TYPE_9__ {int gen; } ;
struct TYPE_8__ {struct drm_i915_private* dev_private; } ;
struct TYPE_7__ {int busaddr; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HWS_PGA ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* INTEL_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_2__* drm_pci_alloc (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_phys_hws_pga(struct intel_ring_buffer *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	u32 addr;

	if (!dev_priv->status_page_dmah) {
		dev_priv->status_page_dmah =
			drm_pci_alloc(ring->dev, PAGE_SIZE, PAGE_SIZE);
		if (!dev_priv->status_page_dmah)
			return -ENOMEM;
	}

	addr = dev_priv->status_page_dmah->busaddr;
	if (INTEL_INFO(ring->dev)->gen >= 4)
		addr |= (dev_priv->status_page_dmah->busaddr >> 28) & 0xf0;
	I915_WRITE(HWS_PGA, addr);

	ring->status_page.page_addr = dev_priv->status_page_dmah->vaddr;
	memset(ring->status_page.page_addr, 0, PAGE_SIZE);

	return 0;
}