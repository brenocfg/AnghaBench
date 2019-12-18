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
typedef  int /*<<< orphan*/  hb_dict_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int HB_FILTER_CROP_SCALE ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ghb_get_job_filter_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_settings_to_preset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_add_filter2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_preset_apply_filters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_preset_apply_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_preset_apply_video (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ghb_finalize_job(GhbValue *settings)
{
    GhbValue *preset, *job;

    preset = ghb_settings_to_preset(settings);
    job    = ghb_dict_get(settings, "Job");

    // Apply selected preset settings
    hb_preset_apply_mux(preset, job);
    hb_preset_apply_video(preset, job);
    hb_preset_apply_filters(preset, job);

    // Add scale filter since the above does not
    GhbValue *filter_list, *filter_dict;
    int width, height, crop[4];

    filter_list = ghb_get_job_filter_list(settings);
    width = ghb_dict_get_int(settings, "scale_width");
    height = ghb_dict_get_int(settings, "scale_height");

    crop[0] = ghb_dict_get_int(settings, "PictureTopCrop");
    crop[1] = ghb_dict_get_int(settings, "PictureBottomCrop");
    crop[2] = ghb_dict_get_int(settings, "PictureLeftCrop");
    crop[3] = ghb_dict_get_int(settings, "PictureRightCrop");

    hb_dict_t * dict = ghb_dict_new();
    ghb_dict_set_int(dict, "width", width);
    ghb_dict_set_int(dict, "height", height);
    ghb_dict_set_int(dict, "crop-top", crop[0]);
    ghb_dict_set_int(dict, "crop-bottom", crop[1]);
    ghb_dict_set_int(dict, "crop-left", crop[2]);
    ghb_dict_set_int(dict, "crop-right", crop[3]);

    filter_dict = ghb_dict_new();
    ghb_dict_set_int(filter_dict, "ID", HB_FILTER_CROP_SCALE);
    ghb_dict_set(filter_dict, "Settings", dict);
    hb_add_filter2(filter_list, filter_dict);

    ghb_value_free(&preset);
}