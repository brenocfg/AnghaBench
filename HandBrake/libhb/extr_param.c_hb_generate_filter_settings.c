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

/* Variables and functions */
#define  HB_FILTER_CHROMA_SMOOTH 144 
#define  HB_FILTER_COMB_DETECT 143 
#define  HB_FILTER_CROP_SCALE 142 
#define  HB_FILTER_DEBLOCK 141 
#define  HB_FILTER_DECOMB 140 
#define  HB_FILTER_DEINTERLACE 139 
#define  HB_FILTER_DETELECINE 138 
#define  HB_FILTER_GRAYSCALE 137 
#define  HB_FILTER_HQDN3D 136 
#define  HB_FILTER_LAPSHARP 135 
#define  HB_FILTER_NLMEANS 134 
#define  HB_FILTER_PAD 133 
#define  HB_FILTER_QSV 132 
#define  HB_FILTER_RENDER_SUB 131 
#define  HB_FILTER_ROTATE 130 
#define  HB_FILTER_UNSHARP 129 
#define  HB_FILTER_VFR 128 
 int /*<<< orphan*/  check_filter_status (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * generate_chroma_smooth_settings (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * generate_generic_settings (int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * generate_lapsharp_settings (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * generate_nlmeans_settings (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * generate_unsharp_settings (char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 scalar_t__ hb_validate_filter_settings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

hb_value_t *
hb_generate_filter_settings(int filter_id, const char *preset, const char *tune,
                            const char *custom)
{
    hb_value_t * settings = NULL;

    switch (filter_id)
    {
        case HB_FILTER_PAD:
        case HB_FILTER_ROTATE:
        case HB_FILTER_CROP_SCALE:
        case HB_FILTER_VFR:
        case HB_FILTER_RENDER_SUB:
        case HB_FILTER_GRAYSCALE:
        case HB_FILTER_QSV:
            settings = hb_parse_filter_settings(custom);
            break;
        case HB_FILTER_NLMEANS:
            settings = generate_nlmeans_settings(preset, tune, custom);
            break;
        case HB_FILTER_CHROMA_SMOOTH:
            settings = generate_chroma_smooth_settings(preset, tune, custom);
            break;
        case HB_FILTER_LAPSHARP:
            settings = generate_lapsharp_settings(preset, tune, custom);
            break;
        case HB_FILTER_UNSHARP:
            settings = generate_unsharp_settings(preset, tune, custom);
            break;
        case HB_FILTER_DEBLOCK:
        case HB_FILTER_COMB_DETECT:
        case HB_FILTER_DECOMB:
        case HB_FILTER_DETELECINE:
        case HB_FILTER_HQDN3D:
        case HB_FILTER_DEINTERLACE:
            settings = generate_generic_settings(filter_id, preset,
                                                 tune, custom);
            break;
        default:
            fprintf(stderr,
                    "hb_generate_filter_settings: Unrecognized filter (%d).\n",
                    filter_id);
            break;
    }
    check_filter_status(filter_id, settings);

    if (settings != NULL &&
        hb_validate_filter_settings(filter_id, settings) == 0)
    {
        return settings;
    }
    hb_value_free(&settings);
    return NULL;
}