#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ VIDEOMODE_resolution_t ;
typedef  int /*<<< orphan*/  VIDEOMODE_MODE_t ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeVideoArea (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,double*,double*,int) ; 
 int /*<<< orphan*/  CropVideoArea (TYPE_1__*,unsigned int*,unsigned int*,double,double) ; 
 int /*<<< orphan*/  CurrentDisplayMode () ; 
 int FALSE ; 
 int /*<<< orphan*/  GetOutArea (unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* PLATFORM_DesktopResolution () ; 
 scalar_t__ PLATFORM_SupportsVideomode (int /*<<< orphan*/ ,int,int) ; 
 int PLATFORM_WindowMaximised () ; 
 int /*<<< orphan*/  RotateResolution (TYPE_1__*) ; 
 int /*<<< orphan*/  SetVideoMode (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateCustomStretch () ; 
 int /*<<< orphan*/  VIDEOMODE_dest_height ; 
 int /*<<< orphan*/  VIDEOMODE_dest_width ; 
 scalar_t__ VIDEOMODE_rotate90 ; 
 TYPE_1__ window_resolution ; 

__attribute__((used)) static int UpdateVideoWindowed(int window_resized)
{
	VIDEOMODE_MODE_t display_mode = CurrentDisplayMode();
#if SUPPORTS_ROTATE_VIDEOMODE
	int rotate = VIDEOMODE_rotate90 && (PLATFORM_SupportsVideomode(display_mode, TRUE, TRUE)
	                                    || PLATFORM_SupportsVideomode(display_mode, FALSE, TRUE));
#else
	int rotate = FALSE;
#endif
	unsigned int out_w, out_h;
	double mult_w, mult_h;
	VIDEOMODE_resolution_t desk_res = *PLATFORM_DesktopResolution();
	VIDEOMODE_resolution_t res = window_resolution;
	VIDEOMODE_resolution_t *max_res;
	int maximised = PLATFORM_WindowMaximised();

	if (rotate)
		RotateResolution(&res);

	GetOutArea(&out_w, &out_h, display_mode);
	UpdateCustomStretch();
	ComputeVideoArea(&res, &desk_res, display_mode, out_w, out_h, &mult_w, &mult_h, rotate);
	if (window_resized || maximised)
		/* If the window was user-resized we don't allow it to grow, only shrink. */
		max_res = &res;
	else
		/* Don't allow the window to be larger than the desktop. */
		max_res = &desk_res;
	CropVideoArea(max_res, &out_w, &out_h, mult_w, mult_h);
	if (!window_resized && !maximised) {
		res.width = VIDEOMODE_dest_width;
		res.height = VIDEOMODE_dest_height;
	}
	SetVideoMode(&res, display_mode, out_w, out_h, TRUE, rotate);
	return TRUE;
}