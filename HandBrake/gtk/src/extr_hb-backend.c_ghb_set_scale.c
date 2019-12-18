#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ scale_busy; int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_picture_settings_deps (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_set_scale_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ghb_settings_combo_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_ui_update_from_settings (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_update_display_aspect_label (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_update_summary_info (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_spin_button_set_increments (int /*<<< orphan*/ ,int,int) ; 

void
ghb_set_scale(signal_user_data_t *ud, gint mode)
{
    if (ud->scale_busy) return;
    ud->scale_busy = TRUE;

    ghb_set_scale_settings(ud->settings, mode);
    ghb_update_summary_info(ud);
    ghb_picture_settings_deps(ud);

    // Step needs to be at least 2 because odd widths cause scaler crash
    // subsampled chroma requires even crop values.
    GtkWidget *widget;
    int mod = ghb_settings_combo_int(ud->settings, "PictureModulus");
    widget = GHB_WIDGET (ud->builder, "scale_width");
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);
    widget = GHB_WIDGET (ud->builder, "scale_height");
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);

    // "PictureLooseCrop" is a flag that says we prefer to crop extra to
    // satisfy alignment constraints rather than scaling to satisfy them.
    gboolean loosecrop = ghb_dict_get_bool(ud->settings, "PictureLooseCrop");
    if (loosecrop)
    {
        widget = GHB_WIDGET (ud->builder, "PictureTopCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);
        widget = GHB_WIDGET (ud->builder, "PictureBottomCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);
        widget = GHB_WIDGET (ud->builder, "PictureLeftCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);
        widget = GHB_WIDGET (ud->builder, "PictureRightCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), mod, 16);
    }
    else
    {
        widget = GHB_WIDGET (ud->builder, "PictureTopCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), 2, 16);
        widget = GHB_WIDGET (ud->builder, "PictureBottomCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), 2, 16);
        widget = GHB_WIDGET (ud->builder, "PictureLeftCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), 2, 16);
        widget = GHB_WIDGET (ud->builder, "PictureRightCrop");
        gtk_spin_button_set_increments (GTK_SPIN_BUTTON(widget), 2, 16);
    }

    ghb_ui_update_from_settings(ud, "autoscale", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureModulus", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureLooseCrop", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureKeepRatio", ud->settings);

    ghb_ui_update_from_settings(ud, "PictureTopCrop", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureBottomCrop", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureLeftCrop", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureRightCrop", ud->settings);

    ghb_ui_update_from_settings(ud, "scale_width", ud->settings);
    ghb_ui_update_from_settings(ud, "scale_height", ud->settings);

    ghb_ui_update_from_settings(ud, "PicturePARWidth", ud->settings);
    ghb_ui_update_from_settings(ud, "PicturePARHeight", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureDisplayWidth", ud->settings);
    ghb_ui_update_from_settings(ud, "PictureDisplayHeight", ud->settings);
    ghb_update_display_aspect_label(ud);
    ud->scale_busy = FALSE;
}