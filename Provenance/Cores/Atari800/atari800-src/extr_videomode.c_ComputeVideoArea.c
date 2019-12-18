#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double height; double width; } ;
typedef  TYPE_1__ VIDEOMODE_resolution_t ;
typedef  size_t VIDEOMODE_MODE_t ;
struct TYPE_6__ {double asp_ratio; double h_mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_SupportsVideomode (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VIDEOMODE_FIT_HEIGHT 134 
#define  VIDEOMODE_FIT_WIDTH 133 
 scalar_t__ VIDEOMODE_KEEP_ASPECT_NONE ; 
 scalar_t__ VIDEOMODE_KEEP_ASPECT_REAL ; 
#define  VIDEOMODE_STRETCH_2X 132 
#define  VIDEOMODE_STRETCH_3X 131 
#define  VIDEOMODE_STRETCH_CUSTOM 130 
#define  VIDEOMODE_STRETCH_INTEGER 129 
#define  VIDEOMODE_STRETCH_NONE 128 
 double VIDEOMODE_custom_stretch ; 
 double VIDEOMODE_dest_height ; 
 double VIDEOMODE_dest_width ; 
 int /*<<< orphan*/  VIDEOMODE_fit ; 
 double VIDEOMODE_host_aspect_ratio_h ; 
 double VIDEOMODE_host_aspect_ratio_w ; 
 scalar_t__ VIDEOMODE_keep_aspect ; 
 int VIDEOMODE_stretch ; 
 TYPE_2__* display_modes ; 

__attribute__((used)) static void ComputeVideoArea(VIDEOMODE_resolution_t const *res, VIDEOMODE_resolution_t const *screen_res,
                             VIDEOMODE_MODE_t display_mode, unsigned int out_w, unsigned int out_h,
                             double *mult_w, double *mult_h, int rotate)
{
	double asp_ratio;
	/* asp_ratio = <Atari pixel aspect ratio>/<host pixel aspect ratio>.
	   If the screen is to be rotated, then <host pixel aspect ratio> gets inverted. */
	if (VIDEOMODE_keep_aspect == VIDEOMODE_KEEP_ASPECT_REAL) {
		if (rotate)
			asp_ratio = display_modes[display_mode].asp_ratio * screen_res->height / VIDEOMODE_host_aspect_ratio_h
			            * VIDEOMODE_host_aspect_ratio_w / screen_res->width;
		else
			asp_ratio = display_modes[display_mode].asp_ratio * screen_res->width / VIDEOMODE_host_aspect_ratio_w
			            * VIDEOMODE_host_aspect_ratio_h / screen_res->height;
	}
	else
		asp_ratio = 1.0 / display_modes[display_mode].h_mult;

	if (!PLATFORM_SupportsVideomode(display_mode, TRUE, rotate)) {
		*mult_w = 1.0;
		*mult_h = display_modes[display_mode].h_mult;
		VIDEOMODE_dest_width = out_w * *mult_w;
		VIDEOMODE_dest_height = out_h * *mult_h;
		return;
	}

	switch (VIDEOMODE_stretch) {
	case VIDEOMODE_STRETCH_NONE:
	case VIDEOMODE_STRETCH_2X:
	case VIDEOMODE_STRETCH_3X:
	case VIDEOMODE_STRETCH_CUSTOM:
		*mult_w = asp_ratio * VIDEOMODE_custom_stretch;
		*mult_h = VIDEOMODE_custom_stretch;
		break;
	case VIDEOMODE_STRETCH_INTEGER:
		{
			unsigned int imult_w = (double) res->width / out_w / asp_ratio;
			unsigned int imult_h = res->height / out_h;
			if (imult_w == 0)
				imult_w = 1;
			if (imult_h == 0)
				imult_h = 1;
			if (VIDEOMODE_keep_aspect == VIDEOMODE_KEEP_ASPECT_NONE) {
				*mult_w = (double)imult_w * asp_ratio;
			} else {
				switch (VIDEOMODE_fit) {
				case VIDEOMODE_FIT_WIDTH:
					imult_h = imult_w;
					break;
				case VIDEOMODE_FIT_HEIGHT:
					break;
				default: /* VIDEOMODE_FIT_BOTH */
					if (imult_w < imult_h)
						imult_h = imult_w;
				}
				*mult_w = (double)imult_h * asp_ratio;
			}
			*mult_h = imult_h;
		}
		break;
	default: /* VIDEOMODE_STRETCH_FULL */
		{
			double imult_w = (double) res->width / out_w / asp_ratio;
			double imult_h = (double) res->height / out_h;
			if (imult_w < 1.0)
				imult_w = 1.0;
			if (imult_h < 1.0)
				imult_h = 1.0;
			if (VIDEOMODE_keep_aspect == VIDEOMODE_KEEP_ASPECT_NONE) {
				*mult_w = imult_w * asp_ratio;
			} else {
				switch (VIDEOMODE_fit) {
				case VIDEOMODE_FIT_WIDTH:
					imult_h = imult_w;
					break;
				case VIDEOMODE_FIT_HEIGHT:
					break;
				default: /* VIDEOMODE_FIT_BOTH */
					if (imult_w < imult_h)
						imult_h = imult_w;
				}
				*mult_w = imult_h * asp_ratio;
			}
			*mult_h = imult_h;
			
		}
	}
	VIDEOMODE_dest_width = *mult_w * out_w;
	VIDEOMODE_dest_height = *mult_h * out_h;
}