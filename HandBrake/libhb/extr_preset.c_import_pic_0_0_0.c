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
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_get_bool (int /*<<< orphan*/ *) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 scalar_t__ hb_value_is_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void import_pic_0_0_0(hb_value_t *preset)
{
    if (hb_value_get_bool(hb_dict_get(preset, "UsesMaxPictureSettings")))
    {
        // UsesMaxPictureSettings was deprecated
        hb_dict_set(preset, "UsesPictureSettings", hb_value_int(2));
    }

    hb_value_t *val = hb_dict_get(preset, "PicturePAR");
    if (hb_value_is_number(val))
    {
        const char *s;
        int pic_par = hb_value_get_int(val);
        switch (pic_par)
        {
            default:
            case 0:
                s = "off";
                break;
            case 1:
                s = "strict";
                break;
            case 2:
                s = "loose";
                break;
            case 3:
                s = "custom";
                break;
        }
        hb_dict_set(preset, "PicturePAR", hb_value_string(s));
    }
    else if (hb_value_type(val) == HB_VALUE_TYPE_STRING)
    {
        const char *v = hb_value_get_string(val);
        const char *s;
        char *end;
        int pic_par = strtol(v, &end, 0);
        if (end != v)
        {
            switch (pic_par)
            {
                default:
                case 2:
                    s = "loose";
                    break;
                case 0:
                    s = "off";
                    break;
                case 1:
                    s = "strict";
                    break;
                case 3:
                    s = "custom";
                    break;
            }
            hb_dict_set(preset, "PicturePAR", hb_value_string(s));
        }
        else
        {
            if (strcasecmp(v, "off") &&
                strcasecmp(v, "strict") &&
                strcasecmp(v, "loose") &&
                strcasecmp(v, "custom"))
            {
                hb_dict_set(preset, "PicturePAR", hb_value_string("loose"));
            }
        }
    }
}