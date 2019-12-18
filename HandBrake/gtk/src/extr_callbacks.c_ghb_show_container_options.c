#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_6__ {int format; } ;
typedef  TYPE_2__ hb_container_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int HB_MUX_MASK_MP4 ; 
 scalar_t__ HB_VCODEC_X264_8BIT ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ghb_lookup_container_by_name (char const*) ; 
 scalar_t__ ghb_settings_video_encoder_codec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ *,int) ; 

void ghb_show_container_options(signal_user_data_t *ud)
{
    GtkWidget *w1, *w2, *w3;
    w1 = GHB_WIDGET(ud->builder, "AlignAVStart");
    w2 = GHB_WIDGET(ud->builder, "Mp4HttpOptimize");
    w3 = GHB_WIDGET(ud->builder, "Mp4iPodCompatible");

    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(ud->settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    gint enc = ghb_settings_video_encoder_codec(ud->settings, "VideoEncoder");

    gtk_widget_set_visible(w1, (mux->format & HB_MUX_MASK_MP4));
    gtk_widget_set_visible(w2, (mux->format & HB_MUX_MASK_MP4));
    gtk_widget_set_visible(w3, (mux->format & HB_MUX_MASK_MP4) &&
                               (enc == HB_VCODEC_X264_8BIT));
}