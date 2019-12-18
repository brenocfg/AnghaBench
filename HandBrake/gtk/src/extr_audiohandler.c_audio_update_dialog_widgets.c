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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  audio_deps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_updates ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_drc_string (double) ; 
 char* get_gain_string (double) ; 
 double get_quality (int,double) ; 
 char* get_quality_string (int,double) ; 
 int ghb_audio_quality_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_bool_value_new (int) ; 
 double ghb_dict_get_double (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_double_value (double) ; 
 int ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_string_value (char*) ; 
 int /*<<< orphan*/  ghb_ui_update (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audio_update_dialog_widgets(signal_user_data_t *ud, GhbValue *asettings)
{
    if (asettings != NULL)
    {
        double gain, drc, quality, qualityx;
        char *s_gain, *s_drc, *s_quality;
        gboolean qe;

        block_updates = TRUE;
        ghb_ui_update(ud, "AudioTrack",
                      ghb_dict_get_value(asettings, "Track"));
        ghb_ui_update(ud, "AudioEncoder",
                      ghb_dict_get_value(asettings, "Encoder"));
        ghb_ui_update(ud, "AudioBitrate",
                      ghb_dict_get_value(asettings, "Bitrate"));
        GhbValue *val = ghb_dict_get_value(asettings, "Name");
        if (val != NULL)
        {
            ghb_ui_update(ud, "AudioTrackName", val);
        }
        else
        {
            ghb_ui_update(ud, "AudioTrackName", ghb_string_value(""));
        }
        ghb_ui_update(ud, "AudioSamplerate",
                      ghb_dict_get_value(asettings, "Samplerate"));
        ghb_ui_update(ud, "AudioMixdown",
                      ghb_dict_get_value(asettings, "Mixdown"));
        ghb_ui_update(ud, "AudioTrackDRCSlider",
                      ghb_dict_get_value(asettings, "DRC"));
        drc = ghb_dict_get_double(asettings, "DRC");
        s_drc = get_drc_string(drc);
        ghb_ui_update(ud, "AudioTrackDRCValue", ghb_string_value(s_drc));
        free(s_drc);
        ghb_ui_update(ud, "AudioTrackGainSlider",
                      ghb_dict_get_value(asettings, "Gain"));
        gain = ghb_dict_get_double(asettings, "Gain");
        s_gain = get_gain_string(gain);
        ghb_ui_update(ud, "AudioTrackGainValue", ghb_string_value(s_gain));

        int codec = ghb_settings_audio_encoder_codec(asettings, "Encoder");
        quality = ghb_dict_get_double(asettings, "Quality");
        qualityx = get_quality(codec, quality);
        ghb_ui_update(ud, "AudioTrackQualityX", ghb_double_value(qualityx));
        s_quality = get_quality_string(codec, quality);
        ghb_ui_update(ud, "AudioTrackQualityValue", ghb_string_value(s_quality));
        free(s_quality);
        // Setting a radio button to FALSE does not automatically make
        // the other one TRUE
        qe = ghb_audio_quality_enabled(asettings);
        if (qe)
        {
            ghb_ui_update(ud, "AudioTrackQualityEnable",
                          ghb_bool_value_new(qe));
        }
        else
        {
            ghb_ui_update(ud, "AudioTrackBitrateEnable",
                          ghb_bool_value_new(!qe));
        }
        block_updates = FALSE;
    }
    audio_deps(ud, asettings, NULL);
}