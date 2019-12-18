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
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {int /*<<< orphan*/  buf_async; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,long) ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ old_encode_dev (int /*<<< orphan*/ ) ; 

int drm_fasync(int fd, struct file *filp, int on)
{
	struct drm_file *priv = filp->private_data;
	struct drm_device *dev = priv->minor->dev;

	DRM_DEBUG("fd = %d, device = 0x%lx\n", fd,
		  (long)old_encode_dev(priv->minor->device));
	return fasync_helper(fd, filp, on, &dev->buf_async);
}