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
typedef  int gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int FALSE ; 
#define  HB_ACODEC_AAC_PASS 146 
#define  HB_ACODEC_AC3 145 
#define  HB_ACODEC_AC3_PASS 144 
#define  HB_ACODEC_CA_AAC 143 
#define  HB_ACODEC_DCA 142 
#define  HB_ACODEC_DCA_HD 141 
#define  HB_ACODEC_DCA_HD_PASS 140 
#define  HB_ACODEC_DCA_PASS 139 
#define  HB_ACODEC_EAC3_PASS 138 
#define  HB_ACODEC_FDK_AAC 137 
#define  HB_ACODEC_FFAAC 136 
#define  HB_ACODEC_FFEAC3 135 
#define  HB_ACODEC_FFFLAC 134 
#define  HB_ACODEC_FFFLAC24 133 
#define  HB_ACODEC_FFTRUEHD 132 
#define  HB_ACODEC_FLAC_PASS 131 
#define  HB_ACODEC_LAME 130 
#define  HB_ACODEC_MP3_PASS 129 
#define  HB_ACODEC_TRUEHD_PASS 128 
 int TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int ghb_get_video_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_log (char*,char*) ; 
 int /*<<< orphan*/  ghb_set_video_preset (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  ghb_settings_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_value_dup (int /*<<< orphan*/ ) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 
 int hb_audio_encoder_get_from_name (char const*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

void
ghb_preset_to_settings(GhbValue *settings, GhbValue *preset)
{
    // Remove legacy x264Option
    ghb_dict_remove(settings, "x264Option");

    // Initialize defaults
    ghb_settings_init(settings, "Initialization");

    // Initialize the ui settings from a preset
    ghb_dict_copy(settings, preset);

    // Fix up all the internal settings that are derived from preset values.

    ghb_dict_set(settings, "scale_height", ghb_value_dup(
        ghb_dict_get_value(settings, "PictureHeight")));

    ghb_dict_set(settings, "scale_width", ghb_value_dup(
        ghb_dict_get_value(settings, "PictureWidth")));

    int width, height, uses_pic, autoscale;

    width    = ghb_dict_get_int(settings, "PictureWidth");
    height   = ghb_dict_get_int(settings, "PictureHeight");
    uses_pic = ghb_dict_get_int(settings, "UsesPictureSettings");

    autoscale = uses_pic != 1 || (width == 0 && height == 0);
    ghb_dict_set_bool(settings, "autoscale", autoscale);
    ghb_dict_set_int(settings, "PictureWidthEnable", !autoscale);
    ghb_dict_set_int(settings, "PictureHeightEnable", !autoscale);

    gint vqtype;

    vqtype = ghb_dict_get_int(settings, "VideoQualityType");

    // VideoQualityType/0/1/2 - vquality_type_/target/bitrate/constant
    // *note: target is no longer used
    switch (vqtype)
    {
    case 0:
    {
        ghb_dict_set_bool(settings, "vquality_type_bitrate", TRUE);
        ghb_dict_set_bool(settings, "vquality_type_constant", FALSE);
    } break;
    case 1:
    {
        ghb_dict_set_bool(settings, "vquality_type_bitrate", TRUE);
        ghb_dict_set_bool(settings, "vquality_type_constant", FALSE);
    } break;
    case 2:
    {
        ghb_dict_set_bool(settings, "vquality_type_bitrate", FALSE);
        ghb_dict_set_bool(settings, "vquality_type_constant", TRUE);
    } break;
    default:
    {
        ghb_dict_set_bool(settings, "vquality_type_bitrate", FALSE);
        ghb_dict_set_bool(settings, "vquality_type_constant", TRUE);
    } break;
    }

    const gchar *mode = ghb_dict_get_string(settings, "VideoFramerateMode");
    if (mode != NULL && strcmp(mode, "cfr") == 0)
    {
        ghb_dict_set_bool(settings, "VideoFramerateCFR", TRUE);
        ghb_dict_set_bool(settings, "VideoFrameratePFR", FALSE);
        ghb_dict_set_bool(settings, "VideoFramerateVFR", FALSE);
    }
    else if (mode != NULL && strcmp(mode, "pfr") == 0)
    {
        ghb_dict_set_bool(settings, "VideoFramerateCFR", FALSE);
        ghb_dict_set_bool(settings, "VideoFrameratePFR", TRUE);
        ghb_dict_set_bool(settings, "VideoFramerateVFR", FALSE);
    }
    else
    {
        ghb_dict_set_bool(settings, "VideoFramerateCFR", FALSE);
        ghb_dict_set_bool(settings, "VideoFrameratePFR", FALSE);
        ghb_dict_set_bool(settings, "VideoFramerateVFR", TRUE);
    }

    int                 encoder;
    const char         *videoPreset;

    encoder      = ghb_get_video_encoder(settings);
    videoPreset  = ghb_dict_get_string(settings, "VideoPreset");
    ghb_set_video_preset(settings, encoder, videoPreset);

    char *videoTune;
    char *tune = NULL;
    char *saveptr;
    char *tok;

    videoTune = g_strdup(ghb_dict_get_string(settings, "VideoTune"));
    if (videoTune != NULL)
    {
        tok = strtok_r(videoTune, ",./-+", &saveptr);
        ghb_dict_set_bool(settings, "x264FastDecode", FALSE);
        ghb_dict_set_bool(settings, "x264ZeroLatency", FALSE);
        while (tok != NULL)
        {
            if (!strcasecmp(tok, "fastdecode"))
            {
                ghb_dict_set_bool(settings, "x264FastDecode", TRUE);
            }
            else if (!strcasecmp(tok, "zerolatency"))
            {
                ghb_dict_set_bool(settings, "x264ZeroLatency", TRUE);
            }
            else if (tune == NULL)
            {
                tune = g_strdup(tok);
            }
            else
            {
                ghb_log("Superfluous tunes! %s", tok);
            }
            tok = strtok_r(NULL, ",./-+", &saveptr);
        }
        g_free(videoTune);
    }
    if (tune != NULL)
    {
        ghb_dict_set_string(settings, "VideoTune", tune);
        g_free(tune);
    }

    const char *videoProfile;
    videoProfile = ghb_dict_get_string(settings, "VideoProfile");
    if (videoProfile != NULL)
        ghb_dict_set_string(settings, "VideoProfile", videoProfile);

    const char *videoLevel;
    videoLevel = ghb_dict_get_string(settings, "VideoLevel");
    if (videoLevel != NULL)
        ghb_dict_set_string(settings, "VideoLevel", videoLevel);

    if (ghb_dict_get(settings, "x264OptionExtra") != NULL)
    {
        const char *optionExtra;
        optionExtra = ghb_dict_get_string(settings, "x264OptionExtra");
        ghb_dict_set_string(settings, "VideoOptionExtra", optionExtra);
    }

    // Extract copy mask to check box booleans
    GhbValue *copy_mask;
    copy_mask = ghb_dict_get(preset, "AudioCopyMask");
    if (copy_mask != NULL)
    {
        int count = ghb_array_len(copy_mask);
        int ii;
        for (ii = 0; ii < count; ii++)
        {
            GhbValue *val = ghb_array_get(copy_mask, ii);
            const char *s = ghb_value_get_string(val);
            int acodec = hb_audio_encoder_get_from_name(s);
            switch (acodec)
            {
                default:
                    break;
                case HB_ACODEC_LAME:
                case HB_ACODEC_MP3_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowMP3Pass", 1);
                    break;
                case HB_ACODEC_CA_AAC:
                case HB_ACODEC_FDK_AAC:
                case HB_ACODEC_FFAAC:
                case HB_ACODEC_AAC_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowAACPass", 1);
                    break;
                case HB_ACODEC_AC3:
                case HB_ACODEC_AC3_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowAC3Pass", 1);
                    break;
                case HB_ACODEC_DCA:
                case HB_ACODEC_DCA_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowDTSPass", 1);
                    break;
                case HB_ACODEC_DCA_HD:
                case HB_ACODEC_DCA_HD_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowDTSHDPass", 1);
                    break;
                case HB_ACODEC_FFEAC3:
                case HB_ACODEC_EAC3_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowEAC3Pass", 1);
                    break;
                case HB_ACODEC_FFFLAC:
                case HB_ACODEC_FFFLAC24:
                case HB_ACODEC_FLAC_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowFLACPass", 1);
                    break;
                case HB_ACODEC_FFTRUEHD:
                case HB_ACODEC_TRUEHD_PASS:
                    ghb_dict_set_bool(settings, "AudioAllowTRUEHDPass", 1);
                    break;
            }
        }
    }
}