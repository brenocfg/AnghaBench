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
 int /*<<< orphan*/  HB_FILTER_DECOMB ; 
 int /*<<< orphan*/  HB_FILTER_DEINTERLACE ; 
 int /*<<< orphan*/  HB_FILTER_DETELECINE ; 
 int /*<<< orphan*/  HB_FILTER_HQDN3D ; 
 int /*<<< orphan*/  HB_FILTER_NLMEANS ; 
 int /*<<< orphan*/  HB_FILTER_ROTATE ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_custom_11_1_0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void import_filters_11_1_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PictureDeinterlaceFilter");
    if (val != NULL)
    {
        const char * str = hb_value_get_string(val);
        if (str != NULL)
        {
            if (strcasecmp(str, "deinterlace"))
            {
                import_custom_11_1_0(preset, HB_FILTER_DEINTERLACE,
                                     "PictureDeinterlaceCustom");
            }
            else if (strcasecmp(str, "decomb"))
            {
                import_custom_11_1_0(preset, HB_FILTER_DECOMB,
                                     "PictureDeinterlaceCustom");
            }
        }
    }
    val = hb_dict_get(preset, "PictureDenoiseFilter");
    if (val != NULL)
    {
        const char * str = hb_value_get_string(val);
        if (str != NULL)
        {
            if (strcasecmp(str, "hqdn3d"))
            {
                import_custom_11_1_0(preset, HB_FILTER_HQDN3D,
                                     "PictureDenoiseCustom");
            }
            else if (strcasecmp(str, "nlmeans"))
            {
                import_custom_11_1_0(preset, HB_FILTER_NLMEANS,
                                     "PictureDenoiseCustom");
            }
        }
    }
    import_custom_11_1_0(preset, HB_FILTER_DETELECINE,
                         "PictureDetelecineCustom");
    import_custom_11_1_0(preset, HB_FILTER_ROTATE,
                         "PictureRotate");
}