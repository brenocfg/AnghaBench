#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  scalar_t__ uint64_t ;
struct vnode_attr {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  v_flag; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIOPINSWAP ; 
 int /*<<< orphan*/  IO_NOZEROFILL ; 
 int /*<<< orphan*/  PROTECTION_CLASS_C ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VNOP_IOCTL (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VNOP_SETATTR (TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSWAP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  va_dataprotect_class ; 
 int /*<<< orphan*/ * vfs_context_kernel () ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int vnode_setsize (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vnode_size (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

int
vm_swapfile_preallocate(vnode_t vp, uint64_t *size, boolean_t *pin)
{
	int		error = 0;
	uint64_t	file_size = 0;
	vfs_context_t	ctx = NULL;
#if CONFIG_FREEZE
	struct vnode_attr va;
#endif /* CONFIG_FREEZE */

	ctx = vfs_context_kernel();

	error = vnode_setsize(vp, *size, IO_NOZEROFILL, ctx);

	if (error) {
		printf("vnode_setsize for swap files failed: %d\n", error);
		goto done;
	}

	error = vnode_size(vp, (off_t*) &file_size, ctx);

	if (error) {
		printf("vnode_size (new file) for swap file failed: %d\n", error);
		goto done;
	}	
	assert(file_size == *size);
	
	if (pin != NULL && *pin != FALSE) {
		error = VNOP_IOCTL(vp, FIOPINSWAP, NULL, 0, ctx);

		if (error) {
			printf("pin for swap files failed: %d,  file_size = %lld\n", error, file_size);
			/* this is not fatal, carry on with files wherever they landed */
			*pin = FALSE;
			error = 0;
		}
	}

	vnode_lock_spin(vp);
	SET(vp->v_flag, VSWAP);
	vnode_unlock(vp);

#if CONFIG_FREEZE
	VATTR_INIT(&va);
	VATTR_SET(&va, va_dataprotect_class, PROTECTION_CLASS_C);
	error = VNOP_SETATTR(vp, &va, ctx);

	if (error) {
		printf("setattr PROTECTION_CLASS_C for swap file failed: %d\n", error);
		goto done;
	}
#endif /* CONFIG_FREEZE */

done:
	return error;
}