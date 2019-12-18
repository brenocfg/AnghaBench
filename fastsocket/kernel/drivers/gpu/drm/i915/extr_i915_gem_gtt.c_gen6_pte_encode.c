#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  gtt_pte_t ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GEN6_PTE_ADDR_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PTE_CACHE_LLC ; 
 int /*<<< orphan*/  GEN6_PTE_CACHE_LLC_MLC ; 
 int /*<<< orphan*/  GEN6_PTE_UNCACHED ; 
 int /*<<< orphan*/  GEN6_PTE_VALID ; 
 int /*<<< orphan*/  HSW_PTE_UNCACHED ; 
#define  I915_CACHE_LLC 130 
#define  I915_CACHE_LLC_MLC 129 
#define  I915_CACHE_NONE 128 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 

__attribute__((used)) static inline gtt_pte_t gen6_pte_encode(struct drm_device *dev,
					dma_addr_t addr,
					enum i915_cache_level level)
{
	gtt_pte_t pte = GEN6_PTE_VALID;
	pte |= GEN6_PTE_ADDR_ENCODE(addr);

	switch (level) {
	case I915_CACHE_LLC_MLC:
		/* Haswell doesn't set L3 this way */
		if (IS_HASWELL(dev))
			pte |= GEN6_PTE_CACHE_LLC;
		else
			pte |= GEN6_PTE_CACHE_LLC_MLC;
		break;
	case I915_CACHE_LLC:
		pte |= GEN6_PTE_CACHE_LLC;
		break;
	case I915_CACHE_NONE:
		if (IS_HASWELL(dev))
			pte |= HSW_PTE_UNCACHED;
		else
			pte |= GEN6_PTE_UNCACHED;
		break;
	default:
		BUG();
	}


	return pte;
}