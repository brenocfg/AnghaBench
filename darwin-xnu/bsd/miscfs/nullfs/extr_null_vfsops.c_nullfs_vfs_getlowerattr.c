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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vfs_attr {int dummy; } ;
typedef  int /*<<< orphan*/  mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFSATTR_INIT (struct vfs_attr*) ; 
 int /*<<< orphan*/  VFSATTR_WANTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_bavail ; 
 int /*<<< orphan*/  f_bfree ; 
 int /*<<< orphan*/  f_blocks ; 
 int /*<<< orphan*/  f_bsize ; 
 int /*<<< orphan*/  f_bused ; 
 int /*<<< orphan*/  f_capabilities ; 
 int /*<<< orphan*/  f_ffree ; 
 int /*<<< orphan*/  f_files ; 
 int /*<<< orphan*/  f_iosize ; 
 int /*<<< orphan*/  memset (struct vfs_attr*,int /*<<< orphan*/ ,int) ; 
 int vfs_getattr (int /*<<< orphan*/ ,struct vfs_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nullfs_vfs_getlowerattr(mount_t mp, struct vfs_attr * vfap, vfs_context_t ctx)
{
	memset(vfap, 0, sizeof(*vfap));
	VFSATTR_INIT(vfap);
	VFSATTR_WANTED(vfap, f_bsize);
	VFSATTR_WANTED(vfap, f_iosize);
	VFSATTR_WANTED(vfap, f_blocks);
	VFSATTR_WANTED(vfap, f_bfree);
	VFSATTR_WANTED(vfap, f_bavail);
	VFSATTR_WANTED(vfap, f_bused);
	VFSATTR_WANTED(vfap, f_files);
	VFSATTR_WANTED(vfap, f_ffree);
	VFSATTR_WANTED(vfap, f_capabilities);

	return vfs_getattr(mp, vfap, ctx);
}