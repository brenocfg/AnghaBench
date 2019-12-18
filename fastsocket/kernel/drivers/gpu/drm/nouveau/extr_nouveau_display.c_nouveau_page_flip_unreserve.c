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
struct nouveau_fence {int dummy; } ;
struct nouveau_bo {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  nouveau_bo_fence (struct nouveau_bo*,struct nouveau_fence*) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (struct nouveau_bo*) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_page_flip_unreserve(struct nouveau_bo *old_bo,
			    struct nouveau_bo *new_bo,
			    struct nouveau_fence *fence)
{
	nouveau_bo_fence(new_bo, fence);
	ttm_bo_unreserve(&new_bo->bo);

	if (likely(old_bo != new_bo)) {
		nouveau_bo_fence(old_bo, fence);
		ttm_bo_unreserve(&old_bo->bo);
	}

	nouveau_bo_unpin(old_bo);
}