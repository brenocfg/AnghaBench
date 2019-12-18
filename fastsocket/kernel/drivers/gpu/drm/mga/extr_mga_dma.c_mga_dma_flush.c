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
struct drm_lock {int flags; } ;
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  WRAP_WAIT_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int _DRM_LOCK_FLUSH ; 
 int _DRM_LOCK_FLUSH_ALL ; 
 int _DRM_LOCK_QUIESCENT ; 
 int /*<<< orphan*/  mga_do_dma_flush (int /*<<< orphan*/ *) ; 
 int mga_do_wait_for_idle (int /*<<< orphan*/ *) ; 

int mga_dma_flush(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	drm_mga_private_t *dev_priv = (drm_mga_private_t *) dev->dev_private;
	struct drm_lock *lock = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("%s%s%s\n",
		  (lock->flags & _DRM_LOCK_FLUSH) ? "flush, " : "",
		  (lock->flags & _DRM_LOCK_FLUSH_ALL) ? "flush all, " : "",
		  (lock->flags & _DRM_LOCK_QUIESCENT) ? "idle, " : "");

	WRAP_WAIT_WITH_RETURN(dev_priv);

	if (lock->flags & (_DRM_LOCK_FLUSH | _DRM_LOCK_FLUSH_ALL))
		mga_do_dma_flush(dev_priv);

	if (lock->flags & _DRM_LOCK_QUIESCENT) {
#if MGA_DMA_DEBUG
		int ret = mga_do_wait_for_idle(dev_priv);
		if (ret < 0)
			DRM_INFO("-EBUSY\n");
		return ret;
#else
		return mga_do_wait_for_idle(dev_priv);
#endif
	} else {
		return 0;
	}
}