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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
struct TYPE_2__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ drm_r128_getparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INIT_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 scalar_t__ DRM_COPY_TO_USER (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  DRM_CURRENTPID ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
#define  R128_PARAM_IRQ_NR 128 
 int drm_dev_to_irq (struct drm_device*) ; 

__attribute__((used)) static int r128_getparam(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_getparam_t *param = data;
	int value;

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d\n", DRM_CURRENTPID);

	switch (param->param) {
	case R128_PARAM_IRQ_NR:
		value = drm_dev_to_irq(dev);
		break;
	default:
		return -EINVAL;
	}

	if (DRM_COPY_TO_USER(param->value, &value, sizeof(int))) {
		DRM_ERROR("copy_to_user\n");
		return -EFAULT;
	}

	return 0;
}