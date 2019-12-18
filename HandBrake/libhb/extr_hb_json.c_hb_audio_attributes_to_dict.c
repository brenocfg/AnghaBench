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
 int HB_AUDIO_ATTR_ALT_COMMENTARY ; 
 int HB_AUDIO_ATTR_COMMENTARY ; 
 int HB_AUDIO_ATTR_DEFAULT ; 
 int HB_AUDIO_ATTR_NORMAL ; 
 int HB_AUDIO_ATTR_SECONDARY ; 
 int HB_AUDIO_ATTR_VISUALLY_IMPAIRED ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

hb_dict_t * hb_audio_attributes_to_dict(uint32_t attributes)
{
    json_error_t error;
    hb_dict_t * dict;

    dict = json_pack_ex(&error, 0,
        "{s:o, s:o, s:o, s:o, s:o, s:o}",
        "Normal",           hb_value_bool(attributes & HB_AUDIO_ATTR_NORMAL),
        "VisuallyImpaired", hb_value_bool(attributes &
                                          HB_AUDIO_ATTR_VISUALLY_IMPAIRED),
        "Commentary",       hb_value_bool(attributes &
                                          HB_AUDIO_ATTR_COMMENTARY),
        "AltCommentary",    hb_value_bool(attributes &
                                          HB_AUDIO_ATTR_ALT_COMMENTARY),
        "Secondary",        hb_value_bool(attributes & HB_AUDIO_ATTR_SECONDARY),
        "Default",          hb_value_bool(attributes & HB_AUDIO_ATTR_DEFAULT));
    if (dict == NULL)
    {
        hb_error("json pack failure: %s", error.text);
    }
    return dict;
}