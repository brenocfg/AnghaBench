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
struct drm_buf {struct drm_file* file_priv; } ;

/* Variables and functions */
 int EBUSY ; 
 struct drm_buf* radeon_freelist_get (struct drm_device*) ; 

__attribute__((used)) static int r600_ib_get(struct drm_device *dev,
			struct drm_file *fpriv,
			struct drm_buf **buffer)
{
	struct drm_buf *buf;

	*buffer = NULL;
	buf = radeon_freelist_get(dev);
	if (!buf) {
		return -EBUSY;
	}
	buf->file_priv = fpriv;
	*buffer = buf;
	return 0;
}