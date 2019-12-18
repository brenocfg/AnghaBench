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
struct dip_infoframe {int type; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
#define  DIP_TYPE_AVI 129 
#define  DIP_TYPE_SPD 128 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_AVI_DATA (int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_SPD_DATA (int) ; 

__attribute__((used)) static u32 hsw_infoframe_data_reg(struct dip_infoframe *frame, enum pipe pipe)
{
	switch (frame->type) {
	case DIP_TYPE_AVI:
		return HSW_TVIDEO_DIP_AVI_DATA(pipe);
	case DIP_TYPE_SPD:
		return HSW_TVIDEO_DIP_SPD_DATA(pipe);
	default:
		DRM_DEBUG_DRIVER("unknown info frame type %d\n", frame->type);
		return 0;
	}
}