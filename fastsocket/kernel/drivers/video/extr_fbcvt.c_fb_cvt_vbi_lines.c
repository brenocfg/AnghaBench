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
struct fb_cvt_data {int flags; int hperiod; int vsync; } ;

/* Variables and functions */
 int FB_CVT_FLAG_REDUCED_BLANK ; 
 int FB_CVT_MIN_BPORCH ; 
 int FB_CVT_MIN_VPORCH ; 
 int FB_CVT_MIN_VSYNC_BP ; 
 int FB_CVT_RB_MIN_VBLANK ; 
 int FB_CVT_RB_V_FPORCH ; 

__attribute__((used)) static u32 fb_cvt_vbi_lines(struct fb_cvt_data *cvt)
{
	u32 vbi_lines, min_vbi_lines, act_vbi_lines;

	if (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK) {
		vbi_lines = (1000 * FB_CVT_RB_MIN_VBLANK)/cvt->hperiod + 1;
		min_vbi_lines =  FB_CVT_RB_V_FPORCH + cvt->vsync +
			FB_CVT_MIN_BPORCH;

	} else {
		vbi_lines = (FB_CVT_MIN_VSYNC_BP * 1000)/cvt->hperiod + 1 +
			 FB_CVT_MIN_VPORCH;
		min_vbi_lines = cvt->vsync + FB_CVT_MIN_BPORCH +
			FB_CVT_MIN_VPORCH;
	}

	if (vbi_lines < min_vbi_lines)
		act_vbi_lines = min_vbi_lines;
	else
		act_vbi_lines = vbi_lines;

	return act_vbi_lines;
}