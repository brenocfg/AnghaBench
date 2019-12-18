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
typedef  int /*<<< orphan*/  u32 ;
struct drm_radeon_private {int /*<<< orphan*/  r600_group_size; int /*<<< orphan*/  r600_nbanks; int /*<<< orphan*/  r600_npipes; } ;
struct drm_device {struct drm_radeon_private* dev_private; } ;

/* Variables and functions */

void r600_cs_legacy_get_tiling_conf(struct drm_device *dev, u32 *npipes, u32 *nbanks, u32 *group_size)
{
	struct drm_radeon_private *dev_priv = dev->dev_private;

	*npipes = dev_priv->r600_npipes;
	*nbanks = dev_priv->r600_nbanks;
	*group_size = dev_priv->r600_group_size;
}