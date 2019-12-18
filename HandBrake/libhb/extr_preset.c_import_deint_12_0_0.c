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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 char* hb_strdup_printf (char*,int,int,int,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void import_deint_12_0_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PictureDeinterlaceFilter");
    if (val == NULL)
    {
        return;
    }
    const char * deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }
    if (strcasecmp(deint, "decomb"))
    {
        return;
    }
    val = hb_dict_get(preset, "PictureDeinterlacePreset");
    if (val == NULL)
    {
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }
    if (!strcasecmp(deint, "fast"))
    {
        // fast -> PictureCombDetectPreset fast
        //         PictureDeinterlacePreset default
        hb_dict_set(preset, "PictureCombDetectPreset",
                    hb_value_string("fast"));
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    else if (!strcasecmp(deint, "bob") || !strcasecmp(deint, "default"))
    {
        hb_dict_set(preset, "PictureCombDetectPreset",
                    hb_value_string("default"));
        return;
    }
    else if (strcasecmp(deint, "custom"))
    {
        // not custom -> default
        hb_dict_set(preset, "PictureCombDetectPreset",
                    hb_value_string("default"));
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    val = hb_dict_get(preset, "PictureDeinterlaceCustom");
    if (val == NULL)
    {
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    // Translate custom values
    deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }

    hb_dict_t * dict;
    dict = hb_parse_filter_settings(deint);

    int yadif, blend, cubic, eedi2, mask, bob, gamma, filter, composite;
    int detect_mode, decomb_mode;

    int mode = 7, spatial_metric = 2, motion_threshold = 3;
    int spatial_threshold = 3, filter_mode = 2;
    int block_threshold = 40, block_width = 16, block_height = 16;
    int magnitude_threshold = 10, variance_threshold = 20;
    int laplacian_threshold = 20;
    int dilation_threshold = 4, erosion_threshold = 2, noise_threshold = 50;
    int maximum_search_distance = 24, post_processing = 1, parity = -1;

    hb_dict_extract_int(&mode, dict, "mode");
    hb_dict_extract_int(&spatial_metric, dict, "spatial-metric");
    hb_dict_extract_int(&motion_threshold, dict, "motion-thresh");
    hb_dict_extract_int(&spatial_threshold, dict, "spatial-thresh");
    hb_dict_extract_int(&filter_mode, dict, "filter-mode");
    hb_dict_extract_int(&block_threshold, dict, "block-thresh");
    hb_dict_extract_int(&block_width, dict, "block-width");
    hb_dict_extract_int(&block_height, dict, "block-height");
    hb_dict_extract_int(&magnitude_threshold, dict, "magnitude-thresh");
    hb_dict_extract_int(&variance_threshold, dict, "variance-thresh");
    hb_dict_extract_int(&laplacian_threshold, dict, "laplacian-thresh");
    hb_dict_extract_int(&dilation_threshold, dict, "dilation-thresh");
    hb_dict_extract_int(&erosion_threshold, dict, "erosion-thresh");
    hb_dict_extract_int(&noise_threshold, dict, "noise-thresh");
    hb_dict_extract_int(&maximum_search_distance, dict, "search-distance");
    hb_dict_extract_int(&post_processing, dict, "postproc");
    hb_dict_extract_int(&parity, dict, "parity");
    hb_value_free(&dict);

    yadif     = !!(mode & 1);
    blend     = !!(mode & 2);
    cubic     = !!(mode & 4);
    eedi2     = !!(mode & 8);
    mask      = !!(mode & 32);
    bob       = !!(mode & 64);
    gamma     = !!(mode & 128);
    filter    = !!(mode & 256);
    composite = !!(mode & 512);

    detect_mode = gamma + filter * 2 + mask * 4 + composite * 8;
    decomb_mode = yadif + blend * 2 + cubic * 4 + eedi2 * 8 + bob * 16;

    char * custom = hb_strdup_printf("mode=%d:spatial-metric=%d:"
                                     "motion-thresh=%d:spatial-thresh=%d:"
                                     "filter-mode=%d:block-thresh=%d:"
                                     "block-width=%d:block-height=%d",
                                     detect_mode, spatial_metric,
                                     motion_threshold, spatial_threshold,
                                     filter_mode, block_threshold,
                                     block_width, block_height);
    hb_dict_set(preset, "PictureCombDetectCustom", hb_value_string(custom));
    free(custom);

    custom = hb_strdup_printf("mode=%d:magnitude-thresh=%d:variance-thresh=%d:"
                              "laplacian-thresh=%d:dilation-thresh=%d:"
                              "erosion-thresh=%d:noise-thresh=%d:"
                              "search-distance=%d:postproc=%d:parity=%d",
                              decomb_mode, magnitude_threshold,
                              variance_threshold, laplacian_threshold,
                              dilation_threshold, erosion_threshold,
                              noise_threshold, maximum_search_distance,
                              post_processing, parity);
    hb_dict_set(preset, "PictureDeinterlaceCustom", hb_value_string(custom));
    free(custom);
}