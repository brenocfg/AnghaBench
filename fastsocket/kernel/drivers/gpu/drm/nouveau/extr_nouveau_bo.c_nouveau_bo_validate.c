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
struct nouveau_bo {int /*<<< orphan*/  placement; int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int
nouveau_bo_validate(struct nouveau_bo *nvbo, bool interruptible,
		    bool no_wait_gpu)
{
	int ret;

	ret = ttm_bo_validate(&nvbo->bo, &nvbo->placement,
			      interruptible, no_wait_gpu);
	if (ret)
		return ret;

	return 0;
}