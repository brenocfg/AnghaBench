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
struct TYPE_2__ {int /*<<< orphan*/  gsm; } ;
struct drm_i915_private {int /*<<< orphan*/  dev; TYPE_1__ gtt; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teardown_scratch_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen6_gmch_remove(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	iounmap(dev_priv->gtt.gsm);
	teardown_scratch_page(dev_priv->dev);
}