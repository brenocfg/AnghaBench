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
struct drm_i915_private {int next_seqno; int /*<<< orphan*/  last_seqno; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int i915_gem_init_seqno (struct drm_device*,int /*<<< orphan*/ ) ; 

int
i915_gem_get_seqno(struct drm_device *dev, u32 *seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* reserve 0 for non-seqno */
	if (dev_priv->next_seqno == 0) {
		int ret = i915_gem_init_seqno(dev, 0);
		if (ret)
			return ret;

		dev_priv->next_seqno = 1;
	}

	*seqno = dev_priv->last_seqno = dev_priv->next_seqno++;
	return 0;
}