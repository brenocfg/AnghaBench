#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_4__ {int width; int height; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int VIDEOMODE_80_column ; 
 size_t VIDEOMODE_HORIZONTAL_CUSTOM ; 
 size_t VIDEOMODE_STRETCH_CUSTOM ; 
 size_t VIDEOMODE_VERTICAL_CUSTOM ; 
 int VIDEOMODE_custom_horizontal_area ; 
 double VIDEOMODE_custom_stretch ; 
 int VIDEOMODE_custom_vertical_area ; 
 size_t VIDEOMODE_fit ; 
 size_t VIDEOMODE_horizontal_area ; 
 int VIDEOMODE_horizontal_offset ; 
 double VIDEOMODE_host_aspect_ratio_h ; 
 double VIDEOMODE_host_aspect_ratio_w ; 
 size_t VIDEOMODE_keep_aspect ; 
 int VIDEOMODE_rotate90 ; 
 size_t VIDEOMODE_stretch ; 
 size_t VIDEOMODE_vertical_area ; 
 int VIDEOMODE_vertical_offset ; 
 int VIDEOMODE_windowed ; 
 size_t current_resolution ; 
 char** fit_cfg_strings ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char** horizontal_area_cfg_strings ; 
 TYPE_3__ init_fs_resolution ; 
 char** keep_aspect_cfg_strings ; 
 TYPE_2__* resolutions ; 
 char** stretch_cfg_strings ; 
 char** vertical_area_cfg_strings ; 
 TYPE_1__ window_resolution ; 

void VIDEOMODE_WriteConfig(FILE *fp) {
	fprintf(fp, "VIDEOMODE_WINDOW_WIDTH=%u\n", window_resolution.width);
	fprintf(fp, "VIDEOMODE_WINDOW_HEIGHT=%u\n", window_resolution.height);
	fprintf(fp, "VIDEOMODE_FULLSCREEN_WIDTH=%u\n", (resolutions == NULL ? init_fs_resolution.width : resolutions[current_resolution].width));
	fprintf(fp, "VIDEOMODE_FULLSCREEN_HEIGHT=%u\n", (resolutions == NULL ? init_fs_resolution.height : resolutions[current_resolution].height));
	fprintf(fp, "VIDEOMODE_WINDOWED=%d\n", VIDEOMODE_windowed);
	if (VIDEOMODE_horizontal_area == VIDEOMODE_HORIZONTAL_CUSTOM)
		fprintf(fp, "VIDEOMODE_HORIZONTAL_AREA=%d\n", VIDEOMODE_custom_horizontal_area);
	else
		fprintf(fp, "VIDEOMODE_HORIZONTAL_AREA=%s\n", horizontal_area_cfg_strings[VIDEOMODE_horizontal_area]);
	if (VIDEOMODE_vertical_area == VIDEOMODE_VERTICAL_CUSTOM)
		fprintf(fp, "VIDEOMODE_VERTICAL_AREA=%d\n", VIDEOMODE_custom_vertical_area);
	else
		fprintf(fp, "VIDEOMODE_VERTICAL_AREA=%s\n", vertical_area_cfg_strings[VIDEOMODE_vertical_area]);
	fprintf(fp, "VIDEOMODE_HORIZONTAL_SHIFT=%d\n", VIDEOMODE_horizontal_offset);
	fprintf(fp, "VIDEOMODE_VERTICAL_SHIFT=%d\n", VIDEOMODE_vertical_offset);
	if (VIDEOMODE_stretch == VIDEOMODE_STRETCH_CUSTOM)
		fprintf(fp, "VIDEOMODE_STRETCH=%g\n", VIDEOMODE_custom_stretch);
	else
		fprintf(fp, "VIDEOMODE_STRETCH=%s\n", stretch_cfg_strings[VIDEOMODE_stretch]);
	fprintf(fp, "VIDEOMODE_FIT=%s\n", fit_cfg_strings[VIDEOMODE_fit]);
	fprintf(fp, "VIDEOMODE_IMAGE_ASPECT=%s\n", keep_aspect_cfg_strings[VIDEOMODE_keep_aspect]);
#if SUPPORTS_ROTATE_VIDEOMODE
	fprintf(fp, "VIDEOMODE_ROTATE90=%d\n", VIDEOMODE_rotate90);
#endif
	fprintf(fp, "VIDEOMODE_HOST_ASPECT_RATIO=%g:%g\n", VIDEOMODE_host_aspect_ratio_w, VIDEOMODE_host_aspect_ratio_h);
#if COLUMN_80
	fprintf(fp, "VIDEOMODE_80_COLUMN=%d\n", VIDEOMODE_80_column);
#endif
}