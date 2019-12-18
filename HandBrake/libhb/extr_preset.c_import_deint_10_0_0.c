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
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hb_value_get_bool (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void import_deint_10_0_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PictureDecombDeinterlace");
    if (val != NULL)
    {
        int decomb_or_deint = hb_value_get_bool(val);
        const char * deint_preset;
        if (decomb_or_deint)
        {
            deint_preset = hb_value_get_string(
                                hb_dict_get(preset, "PictureDecomb"));
        }
        else
        {
            deint_preset = hb_value_get_string(
                                hb_dict_get(preset, "PictureDeinterlace"));
        }
        if (deint_preset != NULL && strcasecmp(deint_preset, "off"))
        {
            hb_dict_set(preset, "PictureDeinterlaceFilter",
                        decomb_or_deint ? hb_value_string("decomb")
                                        : hb_value_string("deinterlace"));
            hb_dict_set(preset, "PictureDeinterlacePreset",
                        hb_value_string(deint_preset));
        }
        else
        {
            hb_dict_set(preset, "PictureDeinterlaceFilter",
                        hb_value_string("off"));
            hb_dict_set(preset, "PictureDeinterlacePreset",
                        hb_value_string("default"));
        }
    }
}