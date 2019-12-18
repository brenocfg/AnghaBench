#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_fpriv {int /*<<< orphan*/  vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;
struct radeon_bo_va {scalar_t__ soffset; } ;
struct radeon_bo {int dummy; } ;
struct drm_radeon_gem_va {int operation; scalar_t__ offset; int flags; int /*<<< orphan*/  handle; scalar_t__ vm_id; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct radeon_fpriv* driver_priv; } ;
struct drm_device {TYPE_2__* pdev; struct radeon_device* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTTY ; 
#define  RADEON_VA_MAP 129 
 scalar_t__ RADEON_VA_RESERVED_SIZE ; 
 void* RADEON_VA_RESULT_ERROR ; 
 int RADEON_VA_RESULT_OK ; 
 int RADEON_VA_RESULT_VA_EXIST ; 
#define  RADEON_VA_UNMAP 128 
 int RADEON_VM_PAGE_SNOOPED ; 
 int RADEON_VM_PAGE_SYSTEM ; 
 int RADEON_VM_PAGE_VALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 struct radeon_bo_va* radeon_vm_bo_find (int /*<<< orphan*/ *,struct radeon_bo*) ; 
 int radeon_vm_bo_set_addr (struct radeon_device*,struct radeon_bo_va*,scalar_t__,int) ; 

int radeon_gem_va_ioctl(struct drm_device *dev, void *data,
			  struct drm_file *filp)
{
	struct drm_radeon_gem_va *args = data;
	struct drm_gem_object *gobj;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_fpriv *fpriv = filp->driver_priv;
	struct radeon_bo *rbo;
	struct radeon_bo_va *bo_va;
	u32 invalid_flags;
	int r = 0;

	if (!rdev->vm_manager.enabled) {
		args->operation = RADEON_VA_RESULT_ERROR;
		return -ENOTTY;
	}

	/* !! DONT REMOVE !!
	 * We don't support vm_id yet, to be sure we don't have have broken
	 * userspace, reject anyone trying to use non 0 value thus moving
	 * forward we can use those fields without breaking existant userspace
	 */
	if (args->vm_id) {
		args->operation = RADEON_VA_RESULT_ERROR;
		return -EINVAL;
	}

	if (args->offset < RADEON_VA_RESERVED_SIZE) {
		dev_err(&dev->pdev->dev,
			"offset 0x%lX is in reserved area 0x%X\n",
			(unsigned long)args->offset,
			RADEON_VA_RESERVED_SIZE);
		args->operation = RADEON_VA_RESULT_ERROR;
		return -EINVAL;
	}

	/* don't remove, we need to enforce userspace to set the snooped flag
	 * otherwise we will endup with broken userspace and we won't be able
	 * to enable this feature without adding new interface
	 */
	invalid_flags = RADEON_VM_PAGE_VALID | RADEON_VM_PAGE_SYSTEM;
	if ((args->flags & invalid_flags)) {
		dev_err(&dev->pdev->dev, "invalid flags 0x%08X vs 0x%08X\n",
			args->flags, invalid_flags);
		args->operation = RADEON_VA_RESULT_ERROR;
		return -EINVAL;
	}
	if (!(args->flags & RADEON_VM_PAGE_SNOOPED)) {
		dev_err(&dev->pdev->dev, "only supported snooped mapping for now\n");
		args->operation = RADEON_VA_RESULT_ERROR;
		return -EINVAL;
	}

	switch (args->operation) {
	case RADEON_VA_MAP:
	case RADEON_VA_UNMAP:
		break;
	default:
		dev_err(&dev->pdev->dev, "unsupported operation %d\n",
			args->operation);
		args->operation = RADEON_VA_RESULT_ERROR;
		return -EINVAL;
	}

	gobj = drm_gem_object_lookup(dev, filp, args->handle);
	if (gobj == NULL) {
		args->operation = RADEON_VA_RESULT_ERROR;
		return -ENOENT;
	}
	rbo = gem_to_radeon_bo(gobj);
	r = radeon_bo_reserve(rbo, false);
	if (r) {
		args->operation = RADEON_VA_RESULT_ERROR;
		drm_gem_object_unreference_unlocked(gobj);
		return r;
	}
	bo_va = radeon_vm_bo_find(&fpriv->vm, rbo);
	if (!bo_va) {
		args->operation = RADEON_VA_RESULT_ERROR;
		drm_gem_object_unreference_unlocked(gobj);
		return -ENOENT;
	}

	switch (args->operation) {
	case RADEON_VA_MAP:
		if (bo_va->soffset) {
			args->operation = RADEON_VA_RESULT_VA_EXIST;
			args->offset = bo_va->soffset;
			goto out;
		}
		r = radeon_vm_bo_set_addr(rdev, bo_va, args->offset, args->flags);
		break;
	case RADEON_VA_UNMAP:
		r = radeon_vm_bo_set_addr(rdev, bo_va, 0, 0);
		break;
	default:
		break;
	}
	args->operation = RADEON_VA_RESULT_OK;
	if (r) {
		args->operation = RADEON_VA_RESULT_ERROR;
	}
out:
	radeon_bo_unreserve(rbo);
	drm_gem_object_unreference_unlocked(gobj);
	return r;
}