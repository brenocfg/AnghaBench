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
typedef  int u8 ;
typedef  int u16 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int I915_READ8 (int) ; 
 int /*<<< orphan*/  I915_WRITE8 (int /*<<< orphan*/ ,int) ; 
 int VGA_AR_DATA_READ ; 
 int /*<<< orphan*/  VGA_AR_INDEX ; 

__attribute__((used)) static u8 i915_read_ar(struct drm_device *dev, u16 st01, u8 reg, u16 palette_enable)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	I915_READ8(st01);
	I915_WRITE8(VGA_AR_INDEX, palette_enable | reg);
	return I915_READ8(VGA_AR_DATA_READ);
}