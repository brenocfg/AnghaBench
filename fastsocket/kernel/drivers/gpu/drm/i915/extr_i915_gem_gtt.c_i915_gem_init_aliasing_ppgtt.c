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
struct i915_hw_ppgtt {struct drm_device* dev; } ;
struct TYPE_2__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gen6_ppgtt_init (struct i915_hw_ppgtt*) ; 
 int /*<<< orphan*/  kfree (struct i915_hw_ppgtt*) ; 
 struct i915_hw_ppgtt* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_init_aliasing_ppgtt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_hw_ppgtt *ppgtt;
	int ret;

	ppgtt = kzalloc(sizeof(*ppgtt), GFP_KERNEL);
	if (!ppgtt)
		return -ENOMEM;

	ppgtt->dev = dev;

	ret = gen6_ppgtt_init(ppgtt);
	if (ret)
		kfree(ppgtt);
	else
		dev_priv->mm.aliasing_ppgtt = ppgtt;

	return ret;
}