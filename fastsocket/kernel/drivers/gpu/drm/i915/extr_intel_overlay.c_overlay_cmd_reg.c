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
struct put_image_params {int format; } ;

/* Variables and functions */
 int I915_OVERLAY_DEPTH_MASK ; 
#define  I915_OVERLAY_NO_SWAP 135 
 int I915_OVERLAY_SWAP_MASK ; 
#define  I915_OVERLAY_UV_SWAP 134 
#define  I915_OVERLAY_YUV410 133 
#define  I915_OVERLAY_YUV411 132 
#define  I915_OVERLAY_YUV420 131 
#define  I915_OVERLAY_YUV422 130 
 int I915_OVERLAY_YUV_PLANAR ; 
#define  I915_OVERLAY_Y_AND_UV_SWAP 129 
#define  I915_OVERLAY_Y_SWAP 128 
 int OCMD_BUFFER0 ; 
 int OCMD_BUF_TYPE_FRAME ; 
 int OCMD_ENABLE ; 
 int OCMD_UV_SWAP ; 
 int OCMD_YUV_410_PLANAR ; 
 int OCMD_YUV_411_PACKED ; 
 int OCMD_YUV_420_PLANAR ; 
 int OCMD_YUV_422_PACKED ; 
 int OCMD_YUV_422_PLANAR ; 
 int OCMD_Y_AND_UV_SWAP ; 
 int OCMD_Y_SWAP ; 

__attribute__((used)) static u32 overlay_cmd_reg(struct put_image_params *params)
{
	u32 cmd = OCMD_ENABLE | OCMD_BUF_TYPE_FRAME | OCMD_BUFFER0;

	if (params->format & I915_OVERLAY_YUV_PLANAR) {
		switch (params->format & I915_OVERLAY_DEPTH_MASK) {
		case I915_OVERLAY_YUV422:
			cmd |= OCMD_YUV_422_PLANAR;
			break;
		case I915_OVERLAY_YUV420:
			cmd |= OCMD_YUV_420_PLANAR;
			break;
		case I915_OVERLAY_YUV411:
		case I915_OVERLAY_YUV410:
			cmd |= OCMD_YUV_410_PLANAR;
			break;
		}
	} else { /* YUV packed */
		switch (params->format & I915_OVERLAY_DEPTH_MASK) {
		case I915_OVERLAY_YUV422:
			cmd |= OCMD_YUV_422_PACKED;
			break;
		case I915_OVERLAY_YUV411:
			cmd |= OCMD_YUV_411_PACKED;
			break;
		}

		switch (params->format & I915_OVERLAY_SWAP_MASK) {
		case I915_OVERLAY_NO_SWAP:
			break;
		case I915_OVERLAY_UV_SWAP:
			cmd |= OCMD_UV_SWAP;
			break;
		case I915_OVERLAY_Y_SWAP:
			cmd |= OCMD_Y_SWAP;
			break;
		case I915_OVERLAY_Y_AND_UV_SWAP:
			cmd |= OCMD_Y_AND_UV_SWAP;
			break;
		}
	}

	return cmd;
}