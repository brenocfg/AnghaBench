#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int xfbHeight; scalar_t__ aa; int /*<<< orphan*/  fbWidth; } ;
typedef  TYPE_1__ GXRModeObj ;

/* Variables and functions */
 int VIDEO_PadFramebufferWidth (int /*<<< orphan*/ ) ; 
 int VI_DISPLAY_PIX_SZ ; 

u32 VIDEO_GetFrameBufferSize(GXRModeObj *rmode) {
	u16 w, h;

	w = VIDEO_PadFramebufferWidth(rmode->fbWidth);
	h = rmode->xfbHeight;

	if (rmode->aa)
		h += 4;

	return w * h * VI_DISPLAY_PIX_SZ;
}