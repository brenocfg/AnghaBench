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
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static void import_anamorphic_20_0_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PicturePAR");
    if (hb_value_type(val) == HB_VALUE_TYPE_STRING)
    {
        const char *s = hb_value_get_string(val);
        if (!strcasecmp(s, "strict"))
        {
            hb_dict_set(preset, "PicturePAR", hb_value_string("loose"));
            hb_dict_set(preset, "UsesPictureSettings", hb_value_int(2));
            hb_dict_set(preset, "PictureModulus", hb_value_int(2));
        }
    }
}