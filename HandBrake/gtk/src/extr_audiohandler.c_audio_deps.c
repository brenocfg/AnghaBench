#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  builder; int /*<<< orphan*/ * settings; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_10__ {int samplerate; int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; } ;
struct TYPE_12__ {TYPE_1__ in; } ;
typedef  TYPE_3__ hb_audio_config_t ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int HB_ACODEC_PASS_FLAG ; 
 int TRUE ; 
 int /*<<< orphan*/  enable_quality_widgets (TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  ghb_adjust_audio_rate_combos (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_check_dependency (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* ghb_get_audio_info (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ghb_grey_combo_options (TYPE_2__*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int,int /*<<< orphan*/ *) ; 
 int ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 int ghb_settings_mixdown_mix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hb_audio_can_apply_drc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
audio_deps(signal_user_data_t *ud, GhbValue *asettings, GtkWidget *widget)
{
    ghb_adjust_audio_rate_combos(ud, asettings);
    ghb_grey_combo_options(ud);
    if (widget != NULL)
        ghb_check_dependency(ud, widget, NULL);

    int track = -1, title_id, mix = 0, acodec = 0, sr = 0;
    hb_audio_config_t *aconfig = NULL;
    const hb_title_t *title;
    gboolean qe;

    title_id = ghb_dict_get_int(ud->settings, "title");
    title = ghb_lookup_title(title_id, NULL);

    if (asettings != NULL)
    {
        track = ghb_dict_get_int(asettings, "Track");
        acodec = ghb_settings_audio_encoder_codec(asettings, "Encoder");
        aconfig = ghb_get_audio_info(title, track);
        mix = ghb_settings_mixdown_mix(asettings, "Mixdown");
        sr = ghb_dict_get_int(asettings, "Samplerate");
        if (sr == 0 && aconfig != NULL)
        {
            sr = aconfig->in.samplerate;
        }
    }

    gboolean is_passthru = (acodec & HB_ACODEC_PASS_FLAG);
    gboolean enable_drc = TRUE;
    if (aconfig != NULL)
    {
        enable_drc = hb_audio_can_apply_drc(aconfig->in.codec,
                                            aconfig->in.codec_param, acodec) &&
                     !is_passthru;
    }

    widget = GHB_WIDGET(ud->builder, "AudioTrackDRCSlider");
    gtk_widget_set_sensitive(widget, enable_drc);
    widget = GHB_WIDGET(ud->builder, "AudioTrackDRCSliderLabel");
    gtk_widget_set_sensitive(widget, enable_drc);
    widget = GHB_WIDGET(ud->builder, "AudioTrackDRCValue");
    gtk_widget_set_sensitive(widget, enable_drc);

    qe = ghb_dict_get_bool(ud->settings, "AudioTrackQualityEnable");
    enable_quality_widgets(ud, qe, acodec, sr, mix);

    widget = GHB_WIDGET(ud->builder, "AudioMixdown");
    gtk_widget_set_sensitive(widget, !is_passthru);
    widget = GHB_WIDGET(ud->builder, "AudioSamplerate");
    gtk_widget_set_sensitive(widget, !is_passthru);
    widget = GHB_WIDGET(ud->builder, "AudioTrackGainSlider");
    gtk_widget_set_sensitive(widget, !is_passthru);
    widget = GHB_WIDGET(ud->builder, "AudioTrackGainValue");
    gtk_widget_set_sensitive(widget, !is_passthru);
}