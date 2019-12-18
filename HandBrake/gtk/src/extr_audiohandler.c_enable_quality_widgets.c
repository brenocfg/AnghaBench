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
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 scalar_t__ HB_INVALID_AUDIO_QUALITY ; 
 int TRUE ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ *,int) ; 
 int hb_audio_bitrate_get_default (int,int,int) ; 
 scalar_t__ hb_audio_quality_get_default (int) ; 

__attribute__((used)) static void enable_quality_widgets(
    signal_user_data_t *ud,
    gboolean            quality_enable,
    int                 acodec,
    int                 sr,
    int                 mix)
{
    GtkWidget *widget;
    gboolean quality_sensitive = TRUE;
    gboolean bitrate_sensitive = TRUE;

    widget = GHB_WIDGET(ud->builder, "AudioBitrate");
    gtk_widget_set_visible(widget, !quality_enable);
    widget = GHB_WIDGET(ud->builder, "AudioTrackQualityBox");
    gtk_widget_set_visible(widget, quality_enable);

    if (hb_audio_quality_get_default(acodec) == HB_INVALID_AUDIO_QUALITY)
    {
        quality_sensitive = FALSE;
    }
    if (hb_audio_bitrate_get_default(acodec, sr, mix) == -1)
    {
        bitrate_sensitive = FALSE;
    }

    if (!quality_sensitive)
    {
        widget = GHB_WIDGET(ud->builder, "AudioTrackBitrateEnable");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),
                                     !quality_sensitive);
    }
    widget = GHB_WIDGET(ud->builder, "AudioTrackQualityEnable");
    gtk_widget_set_sensitive(widget, quality_sensitive);

    widget = GHB_WIDGET(ud->builder, "AudioBitrate");
    gtk_widget_set_sensitive(widget, bitrate_sensitive);
    widget = GHB_WIDGET(ud->builder, "AudioTrackQualityEnableBox");
    gtk_widget_set_sensitive(widget, bitrate_sensitive || quality_sensitive);
    widget = GHB_WIDGET(ud->builder, "AudioTrackQualityBox");
    gtk_widget_set_sensitive(widget, quality_sensitive);
}