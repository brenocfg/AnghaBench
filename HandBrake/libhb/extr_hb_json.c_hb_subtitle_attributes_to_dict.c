#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int HB_SUBTITLE_ATTR_4_3 ; 
 int HB_SUBTITLE_ATTR_CC ; 
 int HB_SUBTITLE_ATTR_CHILDREN ; 
 int HB_SUBTITLE_ATTR_COMMENTARY ; 
 int HB_SUBTITLE_ATTR_DEFAULT ; 
 int HB_SUBTITLE_ATTR_FORCED ; 
 int HB_SUBTITLE_ATTR_LARGE ; 
 int HB_SUBTITLE_ATTR_LETTERBOX ; 
 int HB_SUBTITLE_ATTR_NORMAL ; 
 int HB_SUBTITLE_ATTR_PANSCAN ; 
 int HB_SUBTITLE_ATTR_WIDE ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

hb_dict_t * hb_subtitle_attributes_to_dict(uint32_t attributes)
{
    json_error_t error;
    hb_dict_t * dict;

    dict = json_pack_ex(&error, 0,
        "{s:o, s:o, s:o, s:o, s:o, s:o, s:o, s:o, s:o, s:o, s:o}",
        "Normal",        hb_value_bool(attributes & HB_SUBTITLE_ATTR_NORMAL),
        "Large",         hb_value_bool(attributes & HB_SUBTITLE_ATTR_LARGE),
        "Children",      hb_value_bool(attributes & HB_SUBTITLE_ATTR_CHILDREN),
        "ClosedCaption", hb_value_bool(attributes & HB_SUBTITLE_ATTR_CC),
        "Forced",        hb_value_bool(attributes & HB_SUBTITLE_ATTR_FORCED),
        "Commentary",    hb_value_bool(attributes &
                                       HB_SUBTITLE_ATTR_COMMENTARY),
        "4By3",          hb_value_bool(attributes & HB_SUBTITLE_ATTR_4_3),
        "Wide",          hb_value_bool(attributes & HB_SUBTITLE_ATTR_WIDE),
        "Letterbox",     hb_value_bool(attributes & HB_SUBTITLE_ATTR_LETTERBOX),
        "PanScan",       hb_value_bool(attributes & HB_SUBTITLE_ATTR_PANSCAN),
        "Default",       hb_value_bool(attributes & HB_SUBTITLE_ATTR_DEFAULT));
    if (dict == NULL)
    {
        hb_error("json pack failure: %s", error.text);
    }
    return dict;
}