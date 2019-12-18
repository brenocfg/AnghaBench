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
typedef  int /*<<< orphan*/  u32 ;
struct drm_radeon_private {unsigned int flags; int /*<<< orphan*/  cs_mutex; } ;
struct drm_radeon_cs {int /*<<< orphan*/  cs_id; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* agp_buffer_map; struct drm_radeon_private* dev_private; } ;
struct drm_buf {int offset; } ;
struct TYPE_2__ {int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 unsigned int CHIP_R600 ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 unsigned int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r600_cs_id_emit (struct drm_radeon_private*,int /*<<< orphan*/ *) ; 
 int r600_cs_legacy (struct drm_device*,void*,struct drm_file*,unsigned int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  r600_ib_free (struct drm_device*,struct drm_buf*,struct drm_file*,int,int) ; 
 int r600_ib_get (struct drm_device*,struct drm_file*,struct drm_buf**) ; 

int r600_cs_legacy_ioctl(struct drm_device *dev, void *data, struct drm_file *fpriv)
{
	struct drm_radeon_private *dev_priv = dev->dev_private;
	struct drm_radeon_cs *cs = data;
	struct drm_buf *buf;
	unsigned family;
	int l, r = 0;
	u32 *ib, cs_id = 0;

	if (dev_priv == NULL) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}
	family = dev_priv->flags & RADEON_FAMILY_MASK;
	if (family < CHIP_R600) {
		DRM_ERROR("cs ioctl valid only for R6XX & R7XX in legacy mode\n");
		return -EINVAL;
	}
	mutex_lock(&dev_priv->cs_mutex);
	/* get ib */
	r = r600_ib_get(dev, fpriv, &buf);
	if (r) {
		DRM_ERROR("ib_get failed\n");
		goto out;
	}
	ib = dev->agp_buffer_map->handle + buf->offset;
	/* now parse command stream */
	r = r600_cs_legacy(dev, data,  fpriv, family, ib, &l);
	if (r) {
		goto out;
	}

out:
	r600_ib_free(dev, buf, fpriv, l, r);
	/* emit cs id sequence */
	r600_cs_id_emit(dev_priv, &cs_id);
	cs->cs_id = cs_id;
	mutex_unlock(&dev_priv->cs_mutex);
	return r;
}