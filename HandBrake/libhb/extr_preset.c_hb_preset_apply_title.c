#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_9__ {int num; int den; } ;
struct TYPE_11__ {int width; int height; TYPE_1__ par; } ;
struct TYPE_10__ {TYPE_3__ geometry; int /*<<< orphan*/  crop; int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_2__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  TYPE_3__ hb_geometry_t ;
struct TYPE_12__ {int* crop; int modulus; scalar_t__ mode; int keep; int itu_par; TYPE_3__ geometry; void* maxHeight; void* maxWidth; } ;
typedef  TYPE_4__ hb_geometry_settings_t ;
typedef  int /*<<< orphan*/  const hb_dict_t ;

/* Variables and functions */
 int EVEN (int) ; 
 scalar_t__ HB_ANAMORPHIC_AUTO ; 
 scalar_t__ HB_ANAMORPHIC_CUSTOM ; 
 scalar_t__ HB_ANAMORPHIC_LOOSE ; 
 scalar_t__ HB_ANAMORPHIC_NONE ; 
 scalar_t__ HB_ANAMORPHIC_STRICT ; 
 int HB_FILTER_CROP_SCALE ; 
 int HB_KEEP_DISPLAY_ASPECT ; 
 int HB_KEEP_HEIGHT ; 
 int HB_KEEP_WIDTH ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int MULTIPLE_MOD_DOWN (int,int) ; 
 int /*<<< orphan*/  hb_add_filter2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 TYPE_2__* hb_find_title_by_index (int /*<<< orphan*/ *,int) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_preset_job_add_audio (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ hb_preset_job_add_subtitles (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_set_anamorphic_size2 (TYPE_3__*,TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ hb_validate_filter_settings (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_bool (int) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/  const**) ; 
 int hb_value_get_bool (void*) ; 
 void* hb_value_get_int (void*) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* hb_value_int (int) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int hb_preset_apply_title(hb_handle_t *h, int title_index,
                          const hb_dict_t *preset, hb_dict_t *job_dict)
{
    // Apply preset settings  that requires the title
    hb_title_t *title = hb_find_title_by_index(h, title_index);
    if (title == NULL)
        return -1;

    int chapters = hb_value_get_bool(hb_dict_get(preset, "ChapterMarkers"));
    if (hb_list_count(title->list_chapter) <= 1)
        chapters = 0;

    // Set "Destination" settings in job
    hb_dict_t *dest_dict = hb_dict_get(job_dict, "Destination");
    hb_dict_set(dest_dict, "ChapterMarkers", hb_value_bool(chapters));

    hb_dict_t *filters_dict = hb_dict_get(job_dict, "Filters");
    hb_value_array_t *filter_list = hb_dict_get(filters_dict, "FilterList");

    // Calculate default job geometry settings
    hb_geometry_t srcGeo, resultGeo;
    hb_geometry_settings_t geo;
    int keep_aspect;

    srcGeo = title->geometry;
    if (!hb_value_get_bool(hb_dict_get(preset, "PictureAutoCrop")))
    {
        geo.crop[0] = hb_value_get_int(hb_dict_get(preset, "PictureTopCrop"));
        geo.crop[1] = hb_value_get_int(hb_dict_get(preset, "PictureBottomCrop"));
        geo.crop[2] = hb_value_get_int(hb_dict_get(preset, "PictureLeftCrop"));
        geo.crop[3] = hb_value_get_int(hb_dict_get(preset, "PictureRightCrop"));
    }
    else
    {
        memcpy(geo.crop, title->crop, sizeof(geo.crop));
    }
    geo.modulus = hb_value_get_int(hb_dict_get(preset, "PictureModulus"));
    if (geo.modulus < 2)
        geo.modulus = 2;
    if (hb_value_get_bool(hb_dict_get(preset, "PictureLooseCrop")))
    {
        // Crop a few extra pixels to avoid scaling to fit Modulus
        int extra1, extra2, crop_width, crop_height, width, height;

        crop_width = srcGeo.width - geo.crop[2] - geo.crop[3];
        crop_height = srcGeo.height - geo.crop[0] - geo.crop[1];
        width = MULTIPLE_MOD_DOWN(crop_width, geo.modulus);
        height = MULTIPLE_MOD_DOWN(crop_height, geo.modulus);

        extra1 = EVEN((crop_height - height) / 2);
        extra2 = crop_height - height - extra1;
        geo.crop[0] += extra1;
        geo.crop[1] += extra2;
        extra1 = EVEN((crop_width - width) / 2);
        extra2 = crop_width - width - extra1;
        geo.crop[2] += extra1;
        geo.crop[3] += extra2;
    }
    hb_value_t *ana_mode_value = hb_dict_get(preset, "PicturePAR");
    if (hb_value_type(ana_mode_value) == HB_VALUE_TYPE_STRING)
    {
        const char *s = hb_value_get_string(ana_mode_value);
        if (!strcasecmp(s, "off"))
            geo.mode = HB_ANAMORPHIC_NONE;
        else if (!strcasecmp(s, "strict"))
            geo.mode = HB_ANAMORPHIC_STRICT;
        else if (!strcasecmp(s, "custom"))
            geo.mode = HB_ANAMORPHIC_CUSTOM;
        else if (!strcasecmp(s, "auto"))
            geo.mode = HB_ANAMORPHIC_AUTO;
        else // default loose
            geo.mode = HB_ANAMORPHIC_LOOSE;
    }
    else
    {
        geo.mode = hb_value_get_int(hb_dict_get(preset, "PicturePAR"));
    }
    keep_aspect = hb_value_get_bool(hb_dict_get(preset, "PictureKeepRatio"));
    if (geo.mode == HB_ANAMORPHIC_STRICT ||
        geo.mode == HB_ANAMORPHIC_LOOSE  ||
        geo.mode == HB_ANAMORPHIC_AUTO)
    {
        keep_aspect = 1;
    }
    geo.keep = keep_aspect * HB_KEEP_DISPLAY_ASPECT;
    geo.itu_par = hb_value_get_bool(hb_dict_get(preset, "PictureItuPAR"));
    geo.maxWidth = hb_value_get_int(hb_dict_get(preset, "PictureWidth"));
    geo.maxHeight = hb_value_get_int(hb_dict_get(preset, "PictureHeight"));
    geo.geometry = title->geometry;
    int width = hb_value_get_int(hb_dict_get(preset, "PictureForceWidth"));
    int height = hb_value_get_int(hb_dict_get(preset, "PictureForceHeight"));
    if (width > 0)
    {
        geo.geometry.width = width;
        geo.keep |= HB_KEEP_WIDTH;
    }
    else
    {
        geo.geometry.width -= geo.crop[2] + geo.crop[3];
    }
    if (height > 0)
    {
        geo.geometry.height = height;
        geo.keep |= HB_KEEP_HEIGHT;
    }
    else
    {
        geo.geometry.height -= geo.crop[0] + geo.crop[1];
    }
    if (geo.mode == HB_ANAMORPHIC_CUSTOM && !keep_aspect)
    {
        int dar_width;
        dar_width = hb_value_get_int(hb_dict_get(preset, "PictureDARWidth"));
        if (dar_width > 0)
        {
            geo.geometry.par.num = dar_width;
            geo.geometry.par.den = geo.geometry.width;
        }
        else
        {
            geo.geometry.par.num =
                hb_value_get_int(hb_dict_get(preset, "PicturePARWidth"));
            geo.geometry.par.den =
                hb_value_get_int(hb_dict_get(preset, "PicturePARHeight"));
        }
    }
    hb_set_anamorphic_size2(&srcGeo, &geo, &resultGeo);
    hb_dict_t *par_dict = hb_dict_get(job_dict, "PAR");
    hb_dict_set(par_dict, "Num", hb_value_int(resultGeo.par.num));
    hb_dict_set(par_dict, "Den", hb_value_int(resultGeo.par.den));
    par_dict = NULL;

    hb_dict_t *filter_dict;
    hb_dict_t *filter_settings;

    filter_settings = hb_dict_init();
    hb_dict_set(filter_settings, "width", hb_value_int(resultGeo.width));
    hb_dict_set(filter_settings, "height", hb_value_int(resultGeo.height));
    hb_dict_set(filter_settings, "crop-top", hb_value_int(geo.crop[0]));
    hb_dict_set(filter_settings, "crop-bottom", hb_value_int(geo.crop[1]));
    hb_dict_set(filter_settings, "crop-left", hb_value_int(geo.crop[2]));
    hb_dict_set(filter_settings, "crop-right", hb_value_int(geo.crop[3]));
    if (hb_validate_filter_settings(HB_FILTER_CROP_SCALE, filter_settings))
    {
        hb_error("hb_preset_apply_title: Internal error, invalid CROP_SCALE");
        hb_value_free(&filter_settings);
        goto fail;
    }

    filter_dict = hb_dict_init();
    hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_CROP_SCALE));
    hb_dict_set(filter_dict, "Settings", filter_settings);
    hb_add_filter2(filter_list, filter_dict);
    // Audio settings
    if (hb_preset_job_add_audio(h, title_index, preset, job_dict) != 0)
    {
        goto fail;
    }

    // Subtitle settings
    if (hb_preset_job_add_subtitles(h, title_index, preset, job_dict) != 0)
    {
        goto fail;
    }
    return 0;

fail:
    return -1;
}