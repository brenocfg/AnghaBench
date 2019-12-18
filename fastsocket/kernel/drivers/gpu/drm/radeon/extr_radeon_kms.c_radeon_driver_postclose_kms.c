#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_fpriv {int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ ring_tmp_bo; } ;
struct radeon_bo_va {int dummy; } ;
struct drm_file {struct radeon_fpriv* driver_priv; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ CHIP_CAYMAN ; 
 int /*<<< orphan*/  kfree (struct radeon_fpriv*) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 struct radeon_bo_va* radeon_vm_bo_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_vm_bo_rmv (struct radeon_device*,struct radeon_bo_va*) ; 
 int /*<<< orphan*/  radeon_vm_fini (struct radeon_device*,int /*<<< orphan*/ *) ; 

void radeon_driver_postclose_kms(struct drm_device *dev,
				 struct drm_file *file_priv)
{
	struct radeon_device *rdev = dev->dev_private;

	/* new gpu have virtual address space support */
	if (rdev->family >= CHIP_CAYMAN && file_priv->driver_priv) {
		struct radeon_fpriv *fpriv = file_priv->driver_priv;
		struct radeon_bo_va *bo_va;
		int r;

		r = radeon_bo_reserve(rdev->ring_tmp_bo.bo, false);
		if (!r) {
			bo_va = radeon_vm_bo_find(&fpriv->vm,
						  rdev->ring_tmp_bo.bo);
			if (bo_va)
				radeon_vm_bo_rmv(rdev, bo_va);
			radeon_bo_unreserve(rdev->ring_tmp_bo.bo);
		}

		radeon_vm_fini(rdev, &fpriv->vm);
		kfree(fpriv);
		file_priv->driver_priv = NULL;
	}
}