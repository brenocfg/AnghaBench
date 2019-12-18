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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int HB_FILTER_CHROMA_SMOOTH ; 
 int HB_FILTER_COMB_DETECT ; 
 int HB_FILTER_DEBLOCK ; 
 int HB_FILTER_DECOMB ; 
 int HB_FILTER_DEINTERLACE ; 
 int HB_FILTER_DETELECINE ; 
 int HB_FILTER_GRAYSCALE ; 
 int HB_FILTER_HQDN3D ; 
 int HB_FILTER_LAPSHARP ; 
 int HB_FILTER_NLMEANS ; 
 int HB_FILTER_PAD ; 
 int HB_FILTER_ROTATE ; 
 int HB_FILTER_UNSHARP ; 
 int HB_FILTER_VFR ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_video_framerate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_add_filter2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  hb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/ * hb_generate_filter_settings (int,char const*,char const*,char const*) ; 
 char* hb_strdup_printf (char*,int,int) ; 
 scalar_t__ hb_validate_filter_settings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ hb_value_get_bool (int /*<<< orphan*/ *) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 char const* hb_value_get_string (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_int (int) ; 
 int /*<<< orphan*/ * hb_value_string (char*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_video_framerate_get_limits (int*,int*,int*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

int hb_preset_apply_filters(const hb_dict_t *preset, hb_dict_t *job_dict)
{
    hb_value_t * filters_dict, * filter_list, * filter_dict;
    hb_dict_t  * filter_settings;

    int clock_min, clock_max, clock;
    hb_video_framerate_get_limits(&clock_min, &clock_max, &clock);

    // Create new filters
    filters_dict = hb_dict_init();
    hb_dict_set(job_dict, "Filters", filters_dict);
    filter_list = hb_value_array_init();
    hb_dict_set(filters_dict, "FilterList", filter_list);

    // Detelecine filter
    hb_value_t *detel_val = hb_dict_get(preset, "PictureDetelecine");
    if (detel_val != NULL)
    {
        const char *custom;
        custom = hb_value_get_string(hb_dict_get(preset,
                                                "PictureDetelecineCustom"));
        filter_settings = hb_generate_filter_settings(
            HB_FILTER_DETELECINE, hb_value_get_string(detel_val), NULL, custom);

        if (filter_settings == NULL)
        {
            char *s = hb_value_get_string_xform(detel_val);
            hb_error("Invalid detelecine filter settings (%s)", s);
            free(s);
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_DETELECINE));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    const char *comb_preset;
    comb_preset = hb_value_get_string(hb_dict_get(preset,
                                      "PictureCombDetectPreset"));
    if (comb_preset != NULL)
    {
        const char *comb_custom;
        comb_custom = hb_value_get_string(hb_dict_get(preset,
                                          "PictureCombDetectCustom"));
        filter_settings = hb_generate_filter_settings(HB_FILTER_COMB_DETECT,
                                                comb_preset, NULL, comb_custom);
        if (filter_settings == NULL)
        {
            hb_error("Invalid comb detect filter preset (%s)", comb_preset);
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_COMB_DETECT));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    // Decomb or deinterlace filters
    const char *deint_filter, *deint_preset, *deint_custom;
    deint_filter = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureDeinterlaceFilter"));
    deint_preset = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureDeinterlacePreset"));
    deint_custom = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureDeinterlaceCustom"));
    if (deint_filter != NULL && deint_preset != NULL &&
        strcasecmp(deint_filter, "off"))
    {
        int filter_id;
        if (!strcasecmp(deint_filter, "decomb"))
        {
            filter_id = HB_FILTER_DECOMB;
        }
        else if (!strcasecmp(deint_filter, "deinterlace"))
        {
            filter_id = HB_FILTER_DEINTERLACE;
        }
        else
        {
            hb_error("Invalid deinterlace filter (%s)", deint_filter);
            return -1;
        }
        filter_settings = hb_generate_filter_settings(
                        filter_id, deint_preset, NULL, deint_custom);
        if (filter_settings == NULL)
        {
            hb_error("Invalid deinterlace filter preset (%s)", deint_preset);
            return -1;
        }
        if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(filter_id));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    // Denoise filter
    int denoise;
    hb_value_t *denoise_value = hb_dict_get(preset, "PictureDenoiseFilter");
    denoise = hb_value_type(denoise_value) == HB_VALUE_TYPE_STRING ? (
        !strcasecmp(hb_value_get_string(denoise_value), "off") ? 0 :
        !strcasecmp(hb_value_get_string(denoise_value), "nlmeans") ? 1 : 2) :
        hb_value_get_int(denoise_value);

    if (denoise != 0)
    {
        int filter_id = denoise == 1 ? HB_FILTER_NLMEANS : HB_FILTER_HQDN3D;
        const char *denoise_preset, *denoise_tune, *denoise_custom;
        denoise_preset = hb_value_get_string(
                            hb_dict_get(preset, "PictureDenoisePreset"));
        if (denoise_preset != NULL)
        {
            denoise_tune   = hb_value_get_string(
                        hb_dict_get(preset, "PictureDenoiseTune"));
            denoise_custom = hb_value_get_string(
                        hb_dict_get(preset, "PictureDenoiseCustom"));

            filter_settings = hb_generate_filter_settings(filter_id,
                                denoise_preset, denoise_tune, denoise_custom);
            if (filter_settings == NULL)
            {
                hb_error("Invalid denoise filter settings (%s%s%s)",
                         denoise_preset,
                         denoise_tune ? "," : "",
                         denoise_tune ? denoise_tune : "");
                return -1;
            }
            else if (!hb_dict_get_bool(filter_settings, "disable"))
            {
                filter_dict = hb_dict_init();
                hb_dict_set(filter_dict, "ID", hb_value_int(filter_id));
                hb_dict_set(filter_dict, "Settings", filter_settings);
                hb_add_filter2(filter_list, filter_dict);
            }
            else
            {
                hb_value_free(&filter_settings);
            }
        }
    }

    // Chroma Smooth filter
    const char *chroma_smooth_preset, *chroma_smooth_tune, *chroma_smooth_custom;
    chroma_smooth_preset = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureChromaSmoothPreset"));
    chroma_smooth_tune   = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureChromaSmoothTune"));
    chroma_smooth_custom = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureChromaSmoothCustom"));
    if (chroma_smooth_preset != NULL &&
        strcasecmp(chroma_smooth_preset, "off"))
    {
        int filter_id = HB_FILTER_CHROMA_SMOOTH;
        filter_settings = hb_generate_filter_settings(filter_id,
                            chroma_smooth_preset, chroma_smooth_tune, chroma_smooth_custom);
        if (filter_settings == NULL)
        {
            hb_error("Invalid chroma smooth filter settings (%s%s%s)",
                     chroma_smooth_preset,
                     chroma_smooth_tune ? "," : "",
                     chroma_smooth_tune ? chroma_smooth_tune : "");
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(filter_id));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    // Sharpen filter
    const char *sharpen_filter, *sharpen_preset, *sharpen_tune, *sharpen_custom;
    sharpen_filter = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureSharpenFilter"));
    sharpen_preset = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureSharpenPreset"));
    sharpen_tune   = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureSharpenTune"));
    sharpen_custom = hb_value_get_string(hb_dict_get(preset,
                                                   "PictureSharpenCustom"));
    if (sharpen_filter != NULL && sharpen_preset != NULL &&
        strcasecmp(sharpen_filter, "off"))
    {
        int filter_id;
        if (!strcasecmp(sharpen_filter, "lapsharp"))
        {
            filter_id = HB_FILTER_LAPSHARP;
        }
        else if (!strcasecmp(sharpen_filter, "unsharp"))
        {
            filter_id = HB_FILTER_UNSHARP;
        }
        else
        {
            hb_error("Invalid sharpen filter (%s)", sharpen_filter);
            return -1;
        }
        filter_settings = hb_generate_filter_settings(filter_id,
                            sharpen_preset, sharpen_tune, sharpen_custom);
        if (filter_settings == NULL)
        {
            hb_error("Invalid sharpen filter settings (%s%s%s)",
                     sharpen_preset,
                     sharpen_tune ? "," : "",
                     sharpen_tune ? sharpen_tune : "");
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(filter_id));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    // Deblock filter
    const char * deblock = hb_value_get_string(
                                hb_dict_get(preset, "PictureDeblockPreset"));
    if (deblock != NULL)
    {
        const char * deblock_tune   = hb_value_get_string(
                                hb_dict_get(preset, "PictureDeblockTune"));
        const char * deblock_custom = hb_value_get_string(
                                hb_dict_get(preset, "PictureDeblockCustom"));
        filter_settings = hb_generate_filter_settings(HB_FILTER_DEBLOCK,
                                    deblock, deblock_tune, deblock_custom);
        if (filter_settings == NULL)
        {
            hb_error("Invalid deblock filter settings (%s)", deblock);
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_DEBLOCK));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }

    // Rotate filter
    char *rotate = hb_value_get_string_xform(
                        hb_dict_get(preset, "PictureRotate"));
    if (rotate != NULL)
    {
        filter_settings = hb_generate_filter_settings(HB_FILTER_ROTATE,
                                                      NULL, NULL, rotate);
        if (filter_settings == NULL)
        {
            hb_error("Invalid rotate filter settings (%s)", rotate);
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_ROTATE));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }
    free(rotate);

    // Grayscale filter
    if (hb_value_get_bool(hb_dict_get(preset, "VideoGrayScale")))
    {
        filter_dict = hb_dict_init();
        hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_GRAYSCALE));
        hb_add_filter2(filter_list, filter_dict);
    }

    // Pad filter
    char *pad = hb_value_get_string_xform(hb_dict_get(preset, "PicturePad"));
    if (pad != NULL)
    {
        filter_settings = hb_generate_filter_settings(HB_FILTER_PAD,
                                                      NULL, NULL, pad);
        if (filter_settings == NULL)
        {
            hb_error("Invalid pad filter settings (%s)", pad);
            return -1;
        }
        else if (!hb_dict_get_bool(filter_settings, "disable"))
        {
            filter_dict = hb_dict_init();
            hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_PAD));
            hb_dict_set(filter_dict, "Settings", filter_settings);
            hb_add_filter2(filter_list, filter_dict);
        }
        else
        {
            hb_value_free(&filter_settings);
        }
    }
    free(pad);

    hb_value_t *fr_value = hb_dict_get(preset, "VideoFramerate");
    int vrate_den = get_video_framerate(fr_value);
    if (vrate_den < 0)
    {
        char *str = hb_value_get_string_xform(fr_value);
        hb_error("Invalid video framerate (%s)", str);
        free(str);
        return -1;
    }

    int fr_mode;
    hb_value_t *fr_mode_value = hb_dict_get(preset, "VideoFramerateMode");
    fr_mode = hb_value_type(fr_mode_value) == HB_VALUE_TYPE_STRING ? (
        !strcasecmp(hb_value_get_string(fr_mode_value), "cfr") ? 1 :
        !strcasecmp(hb_value_get_string(fr_mode_value), "pfr") ? 2 : 0) :
        hb_value_get_int(fr_mode_value);

    filter_settings = hb_dict_init();
    if (vrate_den == 0)
    {
        hb_dict_set(filter_settings, "mode", hb_value_int(fr_mode));
    }
    else
    {
        char *str = hb_strdup_printf("%d/%d", clock, vrate_den);
        hb_dict_set(filter_settings, "mode", hb_value_int(fr_mode));
        hb_dict_set(filter_settings, "rate", hb_value_string(str));
        free(str);
    }
    if (hb_validate_filter_settings(HB_FILTER_VFR, filter_settings))
    {
        hb_error("hb_preset_apply_filters: Internal error, invalid VFR");
        hb_value_free(&filter_settings);
        return -1;
    }

    filter_dict = hb_dict_init();
    hb_dict_set(filter_dict, "ID", hb_value_int(HB_FILTER_VFR));
    hb_dict_set(filter_dict, "Settings", filter_settings);
    hb_add_filter2(filter_list, filter_dict);
    return 0;
}