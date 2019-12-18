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
struct vm_area_struct {int dummy; } ;
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ drm_device_is_unplugged (struct drm_device*) ; 
 int drm_mmap_locked (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *priv = filp->private_data;
	struct drm_device *dev = priv->minor->dev;
	int ret;

	if (drm_device_is_unplugged(dev))
		return -ENODEV;

	mutex_lock(&dev->struct_mutex);
	ret = drm_mmap_locked(filp, vma);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}