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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 char** hb_video_encoder_get_presets (int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const* const) ; 

int ghb_set_video_preset(GhbValue *settings, int encoder, const char * preset)
{
    const char * const * videoPresets;
    int                  ii, result = 0;

    videoPresets = hb_video_encoder_get_presets(encoder);
    for (ii = 0; videoPresets && videoPresets[ii]; ii++)
    {
        if (preset != NULL && !strcasecmp(preset, videoPresets[ii]))
        {
            ghb_dict_set_int(settings, "VideoPresetSlider", ii);
            result = 1;
            break;
        }
    }
    if (preset == NULL && videoPresets != NULL)
    {
        // Pick the center 'medium' preset
        ii = ii / 2;
        preset = videoPresets[ii];
        ghb_dict_set_int(settings, "VideoPresetSlider", ii);
        result = 1;
    }
    if (preset != NULL)
    {
        ghb_dict_set_string(settings, "VideoPreset", preset);
    }
    return result;
}