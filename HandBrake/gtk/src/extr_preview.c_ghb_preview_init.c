#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  builder; TYPE_4__* preview; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  preview_t ;
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_6__ {int encode_frame; int live_id; char* vsink; int live_enabled; int /*<<< orphan*/ * play; int /*<<< orphan*/  button_height; int /*<<< orphan*/  button_width; int /*<<< orphan*/  pause; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GstBus ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GST_PIPELINE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* g_malloc0 (int) ; 
 int /*<<< orphan*/  g_message (char*) ; 
 int /*<<< orphan*/  g_object_set (char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  gst_bus_add_watch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* gst_element_factory_make (char*,char*) ; 
 int /*<<< orphan*/  gst_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gst_pipeline_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_size_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  live_preview_cb ; 

void
ghb_preview_init(signal_user_data_t *ud)
{
    GtkWidget *widget;

    ud->preview               = g_malloc0(sizeof(preview_t));
    ud->preview->pause        = TRUE;
    ud->preview->encode_frame = -1;
    ud->preview->live_id      = -1;

    widget = GHB_WIDGET(ud->builder, "preview_button_image");
    gtk_widget_get_size_request(widget, &ud->preview->button_width,
                                        &ud->preview->button_height);

#if defined(_ENABLE_GST)
    GstBus *bus;

    ud->preview->play  = gst_element_factory_make("playbin", "play");
    ud->preview->vsink = gst_element_factory_make("gdkpixbufsink", "pixsink");
    if (ud->preview->play == NULL || ud->preview->vsink == NULL)
    {
        g_message("Couldn't initialize gstreamer. Disabling live preview.");
        GtkWidget *widget = GHB_WIDGET(ud->builder, "live_preview_box");
        gtk_widget_hide (widget);
        widget = GHB_WIDGET(ud->builder, "live_preview_duration_box");
        gtk_widget_hide (widget);
        return;
    }
    else
    {
        g_object_set(ud->preview->vsink, "qos", FALSE,
                                         "max-lateness", (gint64) - 1, NULL);
        g_object_set(ud->preview->play, "video-sink", ud->preview->vsink, NULL);
        g_object_set(ud->preview->play, "subtitle-font-desc",
                                        "sans bold 20", NULL);

        bus = gst_pipeline_get_bus(GST_PIPELINE(ud->preview->play));
        gst_bus_add_watch(bus, live_preview_cb, ud);
        gst_object_unref(bus);
        ud->preview->live_enabled = 1;
    }
#else
    widget = GHB_WIDGET(ud->builder, "live_preview_box");
    gtk_widget_hide (widget);
    widget = GHB_WIDGET(ud->builder, "live_preview_duration_box");
    gtk_widget_hide (widget);
#endif
}