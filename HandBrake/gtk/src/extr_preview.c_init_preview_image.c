#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* preview; int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_7__ {size_t frame; int /*<<< orphan*/ * pix; int /*<<< orphan*/ * scaled_pix; scalar_t__* encoded; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_height (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_get_preview_image (int /*<<< orphan*/  const*,size_t,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t ghb_widget_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_fraction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  live_preview_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  preview_set_size (TYPE_2__*,int,int) ; 

void
init_preview_image(signal_user_data_t *ud)
{
    GtkWidget *widget;
    gint width, height;

    gint title_id, titleindex;
    const hb_title_t *title;

    live_preview_stop(ud);

    title_id = ghb_dict_get_int(ud->settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    if (title == NULL && ud->preview->pix != NULL)
    {
        g_object_unref(ud->preview->pix);
        ud->preview->pix = NULL;
    }
    widget = GHB_WIDGET (ud->builder, "preview_frame");
    ud->preview->frame = ghb_widget_int(widget) - 1;
    if (ud->preview->encoded[ud->preview->frame])
    {
        widget = GHB_WIDGET(ud->builder, "live_progress_box");
        gtk_widget_hide (widget);
        widget = GHB_WIDGET(ud->builder, "live_preview_progress");
        gtk_widget_show (widget);
    }
    else
    {
        widget = GHB_WIDGET(ud->builder, "live_preview_progress");
        gtk_widget_hide (widget);
        widget = GHB_WIDGET(ud->builder, "live_progress_box");
        gtk_widget_show (widget);
        widget = GHB_WIDGET(ud->builder, "live_encode_progress");
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(widget), "");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(widget), 0);
    }
    if (ud->preview->pix != NULL)
        g_object_unref(ud->preview->pix);
    if (ud->preview->scaled_pix != NULL)
        g_object_unref(ud->preview->scaled_pix);

    ud->preview->pix = ghb_get_preview_image(title, ud->preview->frame,
                                             ud, &width, &height);
    if (ud->preview->pix == NULL)
        return;

    int pix_width, pix_height;
    pix_width  = gdk_pixbuf_get_width(ud->preview->pix);
    pix_height = gdk_pixbuf_get_height(ud->preview->pix);
    preview_set_size(ud, pix_width, pix_height);
}