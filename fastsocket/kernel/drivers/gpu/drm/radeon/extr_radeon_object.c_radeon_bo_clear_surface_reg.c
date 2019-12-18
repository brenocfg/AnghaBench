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
struct radeon_surface_reg {int /*<<< orphan*/ * bo; } ;
struct radeon_device {struct radeon_surface_reg* surface_regs; } ;
struct radeon_bo {int surface_reg; struct radeon_device* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_clear_surface_reg (struct radeon_device*,size_t) ; 

__attribute__((used)) static void radeon_bo_clear_surface_reg(struct radeon_bo *bo)
{
	struct radeon_device *rdev = bo->rdev;
	struct radeon_surface_reg *reg;

	if (bo->surface_reg == -1)
		return;

	reg = &rdev->surface_regs[bo->surface_reg];
	radeon_clear_surface_reg(rdev, bo->surface_reg);

	reg->bo = NULL;
	bo->surface_reg = -1;
}