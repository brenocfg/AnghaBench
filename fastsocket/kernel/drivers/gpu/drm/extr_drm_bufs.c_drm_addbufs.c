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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_buf_desc {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_DMA ; 
 int EINVAL ; 
 int _DRM_AGP_BUFFER ; 
 int _DRM_FB_BUFFER ; 
 int _DRM_SG_BUFFER ; 
 int drm_addbufs_agp (struct drm_device*,struct drm_buf_desc*) ; 
 int drm_addbufs_fb (struct drm_device*,struct drm_buf_desc*) ; 
 int drm_addbufs_pci (struct drm_device*,struct drm_buf_desc*) ; 
 int drm_addbufs_sg (struct drm_device*,struct drm_buf_desc*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 

int drm_addbufs(struct drm_device *dev, void *data,
		struct drm_file *file_priv)
{
	struct drm_buf_desc *request = data;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

#if __OS_HAS_AGP
	if (request->flags & _DRM_AGP_BUFFER)
		ret = drm_addbufs_agp(dev, request);
	else
#endif
	if (request->flags & _DRM_SG_BUFFER)
		ret = drm_addbufs_sg(dev, request);
	else if (request->flags & _DRM_FB_BUFFER)
		ret = drm_addbufs_fb(dev, request);
	else
		ret = drm_addbufs_pci(dev, request);

	return ret;
}