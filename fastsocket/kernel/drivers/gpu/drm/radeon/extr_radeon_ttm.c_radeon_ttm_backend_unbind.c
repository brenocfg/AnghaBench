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
struct ttm_tt {int /*<<< orphan*/  num_pages; } ;
struct radeon_ttm_tt {int /*<<< orphan*/  offset; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_gart_unbind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_ttm_backend_unbind(struct ttm_tt *ttm)
{
	struct radeon_ttm_tt *gtt = (void *)ttm;

	radeon_gart_unbind(gtt->rdev, gtt->offset, ttm->num_pages);
	return 0;
}