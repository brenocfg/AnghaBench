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
 int HB_VCODEC_FFMPEG_MASK ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_dup (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_get_bool (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_get_int (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 int hb_video_encoder_get_from_name (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void import_video_0_0_0(hb_value_t *preset)
{
    hb_value_t *val;

    if ((val = hb_dict_get(preset, "x264Preset")) != NULL)
         hb_dict_set(preset, "VideoPreset", hb_value_dup(val));
    if ((val = hb_dict_get(preset, "x264Tune")) != NULL)
         hb_dict_set(preset, "VideoTune", hb_value_dup(val));
    if ((val = hb_dict_get(preset, "h264Profile")) != NULL)
         hb_dict_set(preset, "VideoProfile", hb_value_dup(val));
    if ((val = hb_dict_get(preset, "h264Level")) != NULL)
         hb_dict_set(preset, "VideoLevel", hb_value_dup(val));
    if ((val = hb_dict_get(preset, "x264OptionExtra")) != NULL)
        hb_dict_set(preset, "VideoOptionExtra", hb_value_dup(val));

    // Remove invalid "none" tune from VideoTune.  Frontends should
    // be removing this before saving a preset.
    if ((val = hb_dict_get(preset, "VideoTune")) != NULL)
    {
        const char *tune;
        tune = hb_value_get_string(val);
        // "none" is not a valid tune, but is used by HandBrake
        // to indicate no tune options.
        if (tune != NULL && !strncasecmp(tune, "none", 4))
        {
            tune += 4;
            if (tune[0] == ',')
            {
                tune++;
            }
        }
        if (tune != NULL)
        {
            hb_dict_set(preset, "VideoTune", hb_value_string(tune));
        }
    }

    if (hb_value_get_int(hb_dict_get(preset, "VideoQualityType")) == 0)
    {
        // Target size no longer supported
        hb_dict_set(preset, "VideoQualityType", hb_value_int(1));
    }

    if (hb_value_get_bool(hb_dict_get(preset, "VideoFrameratePFR")))
    {
        hb_dict_set(preset, "VideoFramerateMode", hb_value_string("pfr"));
    }
    else if (hb_value_get_bool(hb_dict_get(preset, "VideoFramerateCFR")))
    {
        hb_dict_set(preset, "VideoFramerateMode", hb_value_string("cfr"));
    }
    else if (hb_value_get_bool(hb_dict_get(preset, "VideoFramerateVFR")))
    {
        hb_dict_set(preset, "VideoFramerateMode", hb_value_string("vfr"));
    }

    const char *enc;
    int codec;
    enc = hb_value_get_string(hb_dict_get(preset, "VideoEncoder"));
    codec = hb_video_encoder_get_from_name(enc);
    if (codec & HB_VCODEC_FFMPEG_MASK)
    {
        if ((val = hb_dict_get(preset, "lavcOption")) != NULL)
            hb_dict_set(preset, "VideoOptionExtra", hb_value_dup(val));
    }
}