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
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_GEN2 (struct drm_device*) ; 

__attribute__((used)) static u32 calc_swidthsw(struct drm_device *dev, u32 offset, u32 width)
{
	u32 mask, shift, ret;
	if (IS_GEN2(dev)) {
		mask = 0x1f;
		shift = 5;
	} else {
		mask = 0x3f;
		shift = 6;
	}
	ret = ((offset + width + mask) >> shift) - (offset >> shift);
	if (!IS_GEN2(dev))
		ret <<= 1;
	ret -= 1;
	return ret << 2;
}