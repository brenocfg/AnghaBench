#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * audio_get_selected_settings (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ui_quality (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_double_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_sanitize_audio_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_ui_update (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void ghb_sanitize_audio_tracks(signal_user_data_t *ud)
{
    int ii;
    GhbValue *alist = ghb_get_job_audio_list(ud->settings);
    int count = ghb_array_len(alist);

    for (ii = 0; ii < count; ii++)
    {
        GhbValue *asettings = ghb_array_get(alist, ii);
        ghb_sanitize_audio_settings(ud->settings, asettings);
    }

    GhbValue *asettings = audio_get_selected_settings(ud, NULL);
    if (asettings != NULL)
    {
        ghb_ui_update(ud, "AudioEncoder",
                      ghb_dict_get_value(asettings, "Encoder"));
        ghb_ui_update(ud, "AudioBitrate",
                      ghb_dict_get_value(asettings, "Bitrate"));
        gdouble quality = get_ui_quality(asettings);
        ghb_ui_update(ud, "AudioTrackQualityX", ghb_double_value(quality));
        ghb_ui_update(ud, "AudioSamplerate",
                      ghb_dict_get_value(asettings, "Samplerate"));
        ghb_ui_update(ud, "AudioMixdown",
                      ghb_dict_get_value(asettings, "Mixdown"));
        ghb_ui_update(ud, "AudioTrackDRCSlider",
                      ghb_dict_get_value(asettings, "DRC"));
    }
}