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
struct TYPE_3__ {int /*<<< orphan*/ * settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gdouble ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int HB_ACODEC_AUTO_PASS ; 
 int HB_ACODEC_PASS_FLAG ; 
 scalar_t__ HB_INVALID_AUDIO_QUALITY ; 
 int /*<<< orphan*/  audio_def_settings_quality_set_sensitive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audio_quality_update_limits (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * audio_settings_get_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_widget (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_audio_bitrate_opts_filter (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ghb_audio_samplerate_opts_filter (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ghb_dict_get_double (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_mix_opts_filter (int /*<<< orphan*/ ,int) ; 
 int ghb_select_fallback (int /*<<< orphan*/ *,int) ; 
 int ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 int ghb_settings_audio_samplerate_rate (int /*<<< orphan*/ *,char*) ; 
 int ghb_settings_mixdown_mix (int /*<<< orphan*/ *,char*) ; 
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_audio_bitrate_get_limits (int,int,int,int*,int*) ; 
 scalar_t__ hb_audio_quality_get_default (int) ; 

void audio_def_set_limits(signal_user_data_t *ud, GtkWidget *widget, gboolean set_default)
{
    GtkListBoxRow *row = audio_settings_get_row(widget);
    gint index = gtk_list_box_row_get_index(row);

    GhbValue *alist = ghb_dict_get_value(ud->settings, "AudioList");
    int count = ghb_array_len(alist);
    if (index < 0 || index >= count)
        return;

    GhbValue *adict = ghb_array_get(alist, index);

    int codec = ghb_settings_audio_encoder_codec(adict, "AudioEncoder");
    int fallback = ghb_settings_audio_encoder_codec(ud->settings,
                                                    "AudioEncoderFallback");
    gdouble quality = ghb_dict_get_double(adict, "AudioTrackQuality");

    // Allow quality settings if the current encoder supports quality
    // or if the encoder is auto-passthru and the fallback encoder
    // supports quality.
    gboolean sensitive =
        hb_audio_quality_get_default(codec) != HB_INVALID_AUDIO_QUALITY ||
        (codec == HB_ACODEC_AUTO_PASS &&
         hb_audio_quality_get_default(fallback) != HB_INVALID_AUDIO_QUALITY);
    audio_def_settings_quality_set_sensitive(GTK_WIDGET(row), sensitive);

    int enc;
    if (sensitive)
    {
        enc = codec;
        if (hb_audio_quality_get_default(codec) == HB_INVALID_AUDIO_QUALITY)
        {
            enc = fallback;
        }
        audio_quality_update_limits(
            find_widget(GTK_WIDGET(row), "AudioTrackQualityX"),
            enc, set_default, quality);
    }

    enc = codec;
    if (enc & HB_ACODEC_PASS_FLAG)
    {
        enc = ghb_select_fallback(ud->settings, enc);
    }
    int sr = ghb_settings_audio_samplerate_rate(adict, "AudioSamplerate");
    int mix = ghb_settings_mixdown_mix(adict, "AudioMixdown");
    int low, high;
    hb_audio_bitrate_get_limits(enc, sr, mix, &low, &high);
    GtkWidget *w = find_widget(GTK_WIDGET(row), "AudioBitrate");
    ghb_audio_bitrate_opts_filter(GTK_COMBO_BOX(w), low, high);
    w = find_widget(GTK_WIDGET(row), "AudioMixdown");
    ghb_mix_opts_filter(GTK_COMBO_BOX(w), enc);
    w = find_widget(GTK_WIDGET(row), "AudioSamplerate");
    ghb_audio_samplerate_opts_filter(GTK_COMBO_BOX(w), enc);
}