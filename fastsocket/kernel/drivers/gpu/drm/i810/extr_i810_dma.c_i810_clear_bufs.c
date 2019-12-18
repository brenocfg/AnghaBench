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
struct drm_device {int /*<<< orphan*/  dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  clear_depth; int /*<<< orphan*/  clear_color; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ drm_i810_clear_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  i810_dma_dispatch_clear (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_clear_bufs(struct drm_device *dev, void *data,
			   struct drm_file *file_priv)
{
	drm_i810_clear_t *clear = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	/* GH: Someone's doing nasty things... */
	if (!dev->dev_private)
		return -EINVAL;

	i810_dma_dispatch_clear(dev, clear->flags,
				clear->clear_color, clear->clear_depth);
	return 0;
}