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

/* Variables and functions */
 int EINVAL ; 
 int I915_OVERLAY_DEPTH_MASK ; 
#define  I915_OVERLAY_YUV410 131 
#define  I915_OVERLAY_YUV411 130 
#define  I915_OVERLAY_YUV420 129 
#define  I915_OVERLAY_YUV422 128 

__attribute__((used)) static int uv_vsubsampling(u32 format)
{
	switch (format & I915_OVERLAY_DEPTH_MASK) {
	case I915_OVERLAY_YUV420:
	case I915_OVERLAY_YUV410:
		return 2;
	case I915_OVERLAY_YUV422:
	case I915_OVERLAY_YUV411:
		return 1;
	default:
		return -EINVAL;
	}
}