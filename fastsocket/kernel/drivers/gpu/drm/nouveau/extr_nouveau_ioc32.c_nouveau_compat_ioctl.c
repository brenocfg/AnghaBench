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
struct file {int dummy; } ;
typedef  int (* drm_ioctl_compat_t ) (struct file*,unsigned int,unsigned long) ;

/* Variables and functions */
 unsigned int DRM_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int DRM_COMMAND_BASE ; 
 unsigned int DRM_IOCTL_NR (unsigned int) ; 
 long drm_compat_ioctl (struct file*,unsigned int,unsigned long) ; 
 int drm_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mga_compat_ioctls ; 
 int nouveau_compat_ioctls (struct file*,unsigned int,unsigned long) ; 
 int stub1 (struct file*,unsigned int,unsigned long) ; 

long nouveau_compat_ioctl(struct file *filp, unsigned int cmd,
			 unsigned long arg)
{
	unsigned int nr = DRM_IOCTL_NR(cmd);
	drm_ioctl_compat_t *fn = NULL;
	int ret;

	if (nr < DRM_COMMAND_BASE)
		return drm_compat_ioctl(filp, cmd, arg);

#if 0
	if (nr < DRM_COMMAND_BASE + DRM_ARRAY_SIZE(mga_compat_ioctls))
		fn = nouveau_compat_ioctls[nr - DRM_COMMAND_BASE];
#endif
	if (fn != NULL)
		ret = (*fn)(filp, cmd, arg);
	else
		ret = drm_ioctl(filp, cmd, arg);

	return ret;
}