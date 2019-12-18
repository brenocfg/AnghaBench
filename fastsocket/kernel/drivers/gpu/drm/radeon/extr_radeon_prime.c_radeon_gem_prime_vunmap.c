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
struct radeon_bo {int /*<<< orphan*/  dma_buf_vmap; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 

void radeon_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct radeon_bo *bo = gem_to_radeon_bo(obj);

	ttm_bo_kunmap(&bo->dma_buf_vmap);
}