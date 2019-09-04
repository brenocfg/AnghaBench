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
typedef  int /*<<< orphan*/  uuid_t ;
struct vfs_attr {int /*<<< orphan*/  f_uuid; } ;
typedef  int /*<<< orphan*/  mount_t ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  volume_uuid; scalar_t__ valid_uuid; } ;
typedef  TYPE_1__ cp_lock_vfs_callback_arg ;

/* Variables and functions */
 int /*<<< orphan*/  FIODEVICELOCKED ; 
 int /*<<< orphan*/  VFSATTR_INIT (struct vfs_attr*) ; 
 int /*<<< orphan*/  VFSATTR_IS_SUPPORTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFSATTR_WANTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS_IOCTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_uuid ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 scalar_t__ vfs_getattr (int /*<<< orphan*/ ,struct vfs_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cp_lock_vfs_callback(mount_t mp, void *arg)
{
	cp_lock_vfs_callback_arg *callback_arg = (cp_lock_vfs_callback_arg *)arg;

	if (callback_arg->valid_uuid)  {
		struct vfs_attr va;
		VFSATTR_INIT(&va);
		VFSATTR_WANTED(&va, f_uuid);

		if (vfs_getattr(mp, &va, vfs_context_current()))
			return 0;

		if (!VFSATTR_IS_SUPPORTED(&va, f_uuid))
			return 0;

		if(memcmp(va.f_uuid, callback_arg->volume_uuid, sizeof(uuid_t)))
			return 0;
	}

	VFS_IOCTL(mp, FIODEVICELOCKED, (void *)(uintptr_t)callback_arg->state, 0, vfs_context_kernel());
	return 0;
}