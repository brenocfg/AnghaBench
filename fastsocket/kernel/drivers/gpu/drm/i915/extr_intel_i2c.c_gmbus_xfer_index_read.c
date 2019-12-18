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
typedef  int u32 ;
struct i2c_msg {int len; int* buf; } ;
struct drm_i915_private {int gpio_mmio_base; } ;

/* Variables and functions */
 scalar_t__ GMBUS5 ; 
 int GMBUS_2BYTE_INDEX_EN ; 
 int GMBUS_CYCLE_INDEX ; 
 int GMBUS_SLAVE_INDEX_SHIFT ; 
 int /*<<< orphan*/  I915_WRITE (scalar_t__,int) ; 
 int gmbus_xfer_read (struct drm_i915_private*,struct i2c_msg*,int) ; 

__attribute__((used)) static int
gmbus_xfer_index_read(struct drm_i915_private *dev_priv, struct i2c_msg *msgs)
{
	int reg_offset = dev_priv->gpio_mmio_base;
	u32 gmbus1_index = 0;
	u32 gmbus5 = 0;
	int ret;

	if (msgs[0].len == 2)
		gmbus5 = GMBUS_2BYTE_INDEX_EN |
			 msgs[0].buf[1] | (msgs[0].buf[0] << 8);
	if (msgs[0].len == 1)
		gmbus1_index = GMBUS_CYCLE_INDEX |
			       (msgs[0].buf[0] << GMBUS_SLAVE_INDEX_SHIFT);

	/* GMBUS5 holds 16-bit index */
	if (gmbus5)
		I915_WRITE(GMBUS5 + reg_offset, gmbus5);

	ret = gmbus_xfer_read(dev_priv, &msgs[1], gmbus1_index);

	/* Clear GMBUS5 after each index transfer */
	if (gmbus5)
		I915_WRITE(GMBUS5 + reg_offset, 0);

	return ret;
}