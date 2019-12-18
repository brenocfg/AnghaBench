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
 int hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void import_deblock_35_0_0(hb_value_t *preset)
{
    int deblock = hb_dict_get_int(preset, "PictureDeblock");

    if (deblock < 5)
    {
        hb_dict_set_string(preset, "PictureDeblockPreset", "off");
    }
    else if (deblock < 7)
    {
        hb_dict_set_string(preset, "PictureDeblockPreset", "medium");
    }
    else
    {
        hb_dict_set_string(preset, "PictureDeblockPreset", "strong");
    }
    hb_dict_set_string(preset, "PictureDeblockTune", "medium");
    hb_dict_set_string(preset, "PictureDeblockCustom",
                       "strength=strong:thresh=20");
    hb_dict_remove(preset, "PictureDeblock");
}