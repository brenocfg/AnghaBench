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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int overlay_physical; } ;
typedef  TYPE_1__ drm_i810_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  I810_WRITE (int,int) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 

__attribute__((used)) static int i810_ov0_flip(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	/* Tell the overlay to update */
	I810_WRITE(0x30000, dev_priv->overlay_physical | 0x80000000);

	return 0;
}