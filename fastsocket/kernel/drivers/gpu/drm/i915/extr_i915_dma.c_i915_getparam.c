#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {int pci_device; TYPE_1__* pdev; TYPE_4__* dev_private; } ;
struct TYPE_10__ {int /*<<< orphan*/  aliasing_ppgtt; } ;
struct TYPE_9__ {int /*<<< orphan*/  allow_batchbuffer; } ;
struct TYPE_11__ {int num_fence_regs; int fence_reg_start; TYPE_3__ mm; int /*<<< orphan*/ * ring; int /*<<< orphan*/  overlay; TYPE_2__ dri1; } ;
typedef  TYPE_4__ drm_i915_private_t ;
struct TYPE_12__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ drm_i915_getparam_t ;
struct TYPE_13__ {int gen; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 size_t BCS ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ DRM_COPY_TO_USER (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int HAS_LLC (struct drm_device*) ; 
#define  I915_PARAM_ALLOW_BATCHBUFFER 152 
#define  I915_PARAM_CHIPSET_ID 151 
#define  I915_PARAM_HAS_ALIASING_PPGTT 150 
#define  I915_PARAM_HAS_BLT 149 
#define  I915_PARAM_HAS_BSD 148 
#define  I915_PARAM_HAS_COHERENT_RINGS 147 
#define  I915_PARAM_HAS_EXECBUF2 146 
#define  I915_PARAM_HAS_EXEC_CONSTANTS 145 
#define  I915_PARAM_HAS_EXEC_HANDLE_LUT 144 
#define  I915_PARAM_HAS_EXEC_NO_RELOC 143 
#define  I915_PARAM_HAS_GEM 142 
#define  I915_PARAM_HAS_GEN7_SOL_RESET 141 
#define  I915_PARAM_HAS_LLC 140 
#define  I915_PARAM_HAS_OVERLAY 139 
#define  I915_PARAM_HAS_PAGEFLIPPING 138 
#define  I915_PARAM_HAS_PINNED_BATCHES 137 
#define  I915_PARAM_HAS_PRIME_VMAP_FLUSH 136 
#define  I915_PARAM_HAS_RELAXED_DELTA 135 
#define  I915_PARAM_HAS_RELAXED_FENCING 134 
#define  I915_PARAM_HAS_SECURE_BATCHES 133 
#define  I915_PARAM_HAS_SEMAPHORES 132 
#define  I915_PARAM_HAS_WAIT_TIMEOUT 131 
#define  I915_PARAM_IRQ_ACTIVE 130 
#define  I915_PARAM_LAST_DISPATCH 129 
#define  I915_PARAM_NUM_FENCES_AVAIL 128 
 TYPE_7__* INTEL_INFO (struct drm_device*) ; 
 int READ_BREADCRUMB (TYPE_4__*) ; 
 size_t VCS ; 
 int capable (int /*<<< orphan*/ ) ; 
 int i915_semaphore_is_enabled (struct drm_device*) ; 
 int intel_ring_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_getparam(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_getparam_t *param = data;
	int value;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	switch (param->param) {
	case I915_PARAM_IRQ_ACTIVE:
		value = dev->pdev->irq ? 1 : 0;
		break;
	case I915_PARAM_ALLOW_BATCHBUFFER:
		value = dev_priv->dri1.allow_batchbuffer ? 1 : 0;
		break;
	case I915_PARAM_LAST_DISPATCH:
		value = READ_BREADCRUMB(dev_priv);
		break;
	case I915_PARAM_CHIPSET_ID:
		value = dev->pci_device;
		break;
	case I915_PARAM_HAS_GEM:
		value = 1;
		break;
	case I915_PARAM_NUM_FENCES_AVAIL:
		value = dev_priv->num_fence_regs - dev_priv->fence_reg_start;
		break;
	case I915_PARAM_HAS_OVERLAY:
		value = dev_priv->overlay ? 1 : 0;
		break;
	case I915_PARAM_HAS_PAGEFLIPPING:
		value = 1;
		break;
	case I915_PARAM_HAS_EXECBUF2:
		/* depends on GEM */
		value = 1;
		break;
	case I915_PARAM_HAS_BSD:
		value = intel_ring_initialized(&dev_priv->ring[VCS]);
		break;
	case I915_PARAM_HAS_BLT:
		value = intel_ring_initialized(&dev_priv->ring[BCS]);
		break;
	case I915_PARAM_HAS_RELAXED_FENCING:
		value = 1;
		break;
	case I915_PARAM_HAS_COHERENT_RINGS:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_CONSTANTS:
		value = INTEL_INFO(dev)->gen >= 4;
		break;
	case I915_PARAM_HAS_RELAXED_DELTA:
		value = 1;
		break;
	case I915_PARAM_HAS_GEN7_SOL_RESET:
		value = 1;
		break;
	case I915_PARAM_HAS_LLC:
		value = HAS_LLC(dev);
		break;
	case I915_PARAM_HAS_ALIASING_PPGTT:
		value = dev_priv->mm.aliasing_ppgtt ? 1 : 0;
		break;
	case I915_PARAM_HAS_WAIT_TIMEOUT:
		value = 1;
		break;
	case I915_PARAM_HAS_SEMAPHORES:
		value = i915_semaphore_is_enabled(dev);
		break;
	case I915_PARAM_HAS_PRIME_VMAP_FLUSH:
		value = 1;
		break;
	case I915_PARAM_HAS_SECURE_BATCHES:
		value = capable(CAP_SYS_ADMIN);
		break;
	case I915_PARAM_HAS_PINNED_BATCHES:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_NO_RELOC:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_HANDLE_LUT:
		value = 1;
		break;
	default:
		DRM_DEBUG_DRIVER("Unknown parameter %d\n",
				 param->param);
		return -EINVAL;
	}

	if (DRM_COPY_TO_USER(param->value, &value, sizeof(int))) {
		DRM_ERROR("DRM_COPY_TO_USER failed\n");
		return -EFAULT;
	}

	return 0;
}