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
struct TYPE_3__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HB_ANAMORPHIC_AUTO ; 
 scalar_t__ HB_ANAMORPHIC_CUSTOM ; 
 scalar_t__ HB_ANAMORPHIC_LOOSE ; 
 scalar_t__ HB_ANAMORPHIC_STRICT ; 
 int ghb_dict_get_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ghb_settings_combo_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 

void
ghb_picture_settings_deps(signal_user_data_t *ud)
{
    gboolean autoscale, keep_aspect, enable_keep_aspect;
    gboolean enable_scale_width, enable_scale_height;
    gboolean enable_disp_width, enable_disp_height, enable_par;
    gint pic_par;
    GtkWidget *widget;

    pic_par = ghb_settings_combo_int(ud->settings, "PicturePAR");
    enable_keep_aspect = (pic_par != HB_ANAMORPHIC_STRICT &&
                          pic_par != HB_ANAMORPHIC_AUTO   &&
                          pic_par != HB_ANAMORPHIC_LOOSE);
    keep_aspect = ghb_dict_get_bool(ud->settings, "PictureKeepRatio");
    autoscale = ghb_dict_get_bool(ud->settings, "autoscale");

    enable_scale_width = enable_scale_height =
                         !autoscale && (pic_par != HB_ANAMORPHIC_STRICT);
    enable_disp_width = (pic_par == HB_ANAMORPHIC_CUSTOM) && !keep_aspect;
    enable_par = (pic_par == HB_ANAMORPHIC_CUSTOM) && !keep_aspect;
    enable_disp_height = FALSE;

    widget = GHB_WIDGET(ud->builder, "PictureModulus");
    gtk_widget_set_sensitive(widget, pic_par != HB_ANAMORPHIC_STRICT);
    widget = GHB_WIDGET(ud->builder, "PictureLooseCrop");
    gtk_widget_set_sensitive(widget, pic_par != HB_ANAMORPHIC_STRICT);
    widget = GHB_WIDGET(ud->builder, "scale_width");
    gtk_widget_set_sensitive(widget, enable_scale_width);
    widget = GHB_WIDGET(ud->builder, "scale_height");
    gtk_widget_set_sensitive(widget, enable_scale_height);
    widget = GHB_WIDGET(ud->builder, "PictureDisplayWidth");
    gtk_widget_set_sensitive(widget, enable_disp_width);
    widget = GHB_WIDGET(ud->builder, "PictureDisplayHeight");
    gtk_widget_set_sensitive(widget, enable_disp_height);
    widget = GHB_WIDGET(ud->builder, "PicturePARWidth");
    gtk_widget_set_sensitive(widget, enable_par);
    widget = GHB_WIDGET(ud->builder, "PicturePARHeight");
    gtk_widget_set_sensitive(widget, enable_par);
    widget = GHB_WIDGET(ud->builder, "PictureKeepRatio");
    gtk_widget_set_sensitive(widget, enable_keep_aspect);
    widget = GHB_WIDGET(ud->builder, "autoscale");
    gtk_widget_set_sensitive(widget, pic_par != HB_ANAMORPHIC_STRICT);
}