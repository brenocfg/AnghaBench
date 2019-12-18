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
typedef  int uint32_t ;
struct drm_prime_handle {int flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* prime_handle_to_fd ) (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_PRIME ; 
 int DRM_CLOEXEC ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int drm_prime_handle_to_fd_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file_priv)
{
	struct drm_prime_handle *args = data;
	uint32_t flags;

	if (!drm_core_check_feature(dev, DRIVER_PRIME))
		return -EINVAL;

	if (!dev->driver->prime_handle_to_fd)
		return -ENOSYS;

	/* check flags are valid */
	if (args->flags & ~DRM_CLOEXEC)
		return -EINVAL;

	/* we only want to pass DRM_CLOEXEC which is == O_CLOEXEC */
	flags = args->flags & DRM_CLOEXEC;

	return dev->driver->prime_handle_to_fd(dev, file_priv,
			args->handle, flags, &args->fd);
}