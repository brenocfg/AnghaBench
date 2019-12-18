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
 int /*<<< orphan*/  HB_FILTER_HQDN3D ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_is_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 char* import_indexed_filter (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void import_denoise_0_0_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PictureDenoise");
    if (hb_value_is_number(val))
    {
        const char *s;
        int index = hb_value_get_int(val);
        s = import_indexed_filter(HB_FILTER_HQDN3D, index);
        if (s != NULL)
        {
            hb_dict_set(preset, "PictureDenoiseFilter",
                        hb_value_string("hqdn3d"));
            hb_dict_set(preset, "PictureDenoisePreset", hb_value_string(s));
        }
        else
        {
            if (index != 0)
                hb_error("Invalid denoise index %d", index);
            hb_dict_set(preset, "PictureDenoiseFilter", hb_value_string("off"));
        }
    }
}