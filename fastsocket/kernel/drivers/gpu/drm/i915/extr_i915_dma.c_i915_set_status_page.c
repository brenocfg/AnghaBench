#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int gfx_addr; int page_addr; } ;
struct intel_ring_buffer {TYPE_3__ status_page; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_4__* dev_private; } ;
struct TYPE_8__ {int /*<<< orphan*/ * gfx_hws_cpu_addr; } ;
struct TYPE_7__ {scalar_t__ mappable_base; } ;
struct TYPE_10__ {TYPE_2__ dri1; TYPE_1__ gtt; } ;
typedef  TYPE_4__ drm_i915_private_t ;
struct TYPE_11__ {int addr; } ;
typedef  TYPE_5__ drm_i915_hws_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HWS_PGA ; 
 int /*<<< orphan*/  I915_NEED_GFX_HWS (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct intel_ring_buffer* LP_RING (TYPE_4__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_dma_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/ * ioremap_wc (scalar_t__,int) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_set_status_page(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_hws_addr_t *hws = data;
	struct intel_ring_buffer *ring;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!I915_NEED_GFX_HWS(dev))
		return -EINVAL;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		WARN(1, "tried to set status page when mode setting active\n");
		return 0;
	}

	DRM_DEBUG_DRIVER("set status page addr 0x%08x\n", (u32)hws->addr);

	ring = LP_RING(dev_priv);
	ring->status_page.gfx_addr = hws->addr & (0x1ffff<<12);

	dev_priv->dri1.gfx_hws_cpu_addr =
		ioremap_wc(dev_priv->gtt.mappable_base + hws->addr, 4096);
	if (dev_priv->dri1.gfx_hws_cpu_addr == NULL) {
		i915_dma_cleanup(dev);
		ring->status_page.gfx_addr = 0;
		DRM_ERROR("can not ioremap virtual address for"
				" G33 hw status page\n");
		return -ENOMEM;
	}

	memset_io(dev_priv->dri1.gfx_hws_cpu_addr, 0, PAGE_SIZE);
	I915_WRITE(HWS_PGA, ring->status_page.gfx_addr);

	DRM_DEBUG_DRIVER("load hws HWS_PGA with gfx mem 0x%x\n",
			 ring->status_page.gfx_addr);
	DRM_DEBUG_DRIVER("load hws at %p\n",
			 ring->status_page.page_addr);
	return 0;
}