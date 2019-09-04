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
struct vfstable {int /*<<< orphan*/  vfc_name; struct vfstable* vfc_next; } ;
typedef  int /*<<< orphan*/  mount_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vfs_rootmountalloc_internal (struct vfstable*,char const*) ; 
 struct vfstable* vfsconf ; 

errno_t
vfs_rootmountalloc(const char *fstypename, const char *devname, mount_t *mpp)
{
        struct vfstable *vfsp;

	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
	        if (!strncmp(vfsp->vfc_name, fstypename,
			     sizeof(vfsp->vfc_name)))
		        break;
        if (vfsp == NULL)
	        return (ENODEV);

	*mpp = vfs_rootmountalloc_internal(vfsp, devname);

	if (*mpp)
	        return (0);

	return (ENOMEM);
}