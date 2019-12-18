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
struct nouveau_bo {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 scalar_t__ likely (int) ; 
 int nouveau_bo_pin (struct nouveau_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (struct nouveau_bo*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_page_flip_reserve(struct nouveau_bo *old_bo,
			  struct nouveau_bo *new_bo)
{
	int ret;

	ret = nouveau_bo_pin(new_bo, TTM_PL_FLAG_VRAM);
	if (ret)
		return ret;

	ret = ttm_bo_reserve(&new_bo->bo, false, false, false, 0);
	if (ret)
		goto fail;

	if (likely(old_bo != new_bo)) {
		ret = ttm_bo_reserve(&old_bo->bo, false, false, false, 0);
		if (ret)
			goto fail_unreserve;
	}

	return 0;

fail_unreserve:
	ttm_bo_unreserve(&new_bo->bo);
fail:
	nouveau_bo_unpin(new_bo);
	return ret;
}