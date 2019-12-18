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
typedef  int /*<<< orphan*/  VIDEOMODE_resolution_t ;
typedef  int /*<<< orphan*/  VIDEOMODE_MODE_t ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeVideoArea (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,double*,double*,int) ; 
 int /*<<< orphan*/  CropVideoArea (int /*<<< orphan*/ *,unsigned int*,unsigned int*,double,double) ; 
 int /*<<< orphan*/  CurrentDisplayMode () ; 
 int FALSE ; 
 int /*<<< orphan*/  GetOutArea (unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ PLATFORM_SupportsVideomode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ResolutionForMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RotateResolution (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetVideoMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateCustomStretch () ; 
 scalar_t__ VIDEOMODE_rotate90 ; 

__attribute__((used)) static int UpdateVideoFullscreen(void)
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
	VIDEOMODE_resolution_t *res_for_mode = ResolutionForMode(display_mode, rotate);
	VIDEOMODE_resolution_t res;
	if (res_for_mode == NULL)
		return FALSE;

	res = *res_for_mode;
	if (rotate)
		RotateResolution(&res);

	GetOutArea(&out_w, &out_h, display_mode);
	UpdateCustomStretch();
	ComputeVideoArea(&res, res_for_mode, display_mode, out_w, out_h, &mult_w, &mult_h, rotate);
	CropVideoArea(&res, &out_w, &out_h, mult_w, mult_h);
	SetVideoMode(&res, display_mode, out_w, out_h, FALSE, rotate);
	return TRUE;
}