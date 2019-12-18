#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
struct TYPE_6__ {int func; } ;
typedef  TYPE_1__ drm_r128_depth_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DEV_INIT_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
#define  R128_READ_PIXELS 131 
#define  R128_READ_SPAN 130 
#define  R128_WRITE_PIXELS 129 
#define  R128_WRITE_SPAN 128 
 int /*<<< orphan*/  RING_SPACE_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int r128_cce_dispatch_read_pixels (struct drm_device*,TYPE_1__*) ; 
 int r128_cce_dispatch_read_span (struct drm_device*,TYPE_1__*) ; 
 int r128_cce_dispatch_write_pixels (struct drm_device*,TYPE_1__*) ; 
 int r128_cce_dispatch_write_span (struct drm_device*,TYPE_1__*) ; 

__attribute__((used)) static int r128_cce_depth(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_depth_t *depth = data;
	int ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	ret = -EINVAL;
	switch (depth->func) {
	case R128_WRITE_SPAN:
		ret = r128_cce_dispatch_write_span(dev, depth);
		break;
	case R128_WRITE_PIXELS:
		ret = r128_cce_dispatch_write_pixels(dev, depth);
		break;
	case R128_READ_SPAN:
		ret = r128_cce_dispatch_read_span(dev, depth);
		break;
	case R128_READ_PIXELS:
		ret = r128_cce_dispatch_read_pixels(dev, depth);
		break;
	}

	COMMIT_RING();
	return ret;
}