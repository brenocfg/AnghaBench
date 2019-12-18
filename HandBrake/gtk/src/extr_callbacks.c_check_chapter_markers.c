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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ghb_settings_combo_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
check_chapter_markers(signal_user_data_t *ud)
{
    GtkWidget *widget;
    gint start, end;

    if (ghb_settings_combo_int(ud->settings, "PtoPType") == 0)
    {
        start = ghb_dict_get_int(ud->settings, "start_point");
        end = ghb_dict_get_int(ud->settings, "end_point");
        widget = GHB_WIDGET (ud->builder, "ChapterMarkers");
        gtk_widget_set_sensitive(widget, end > start);
    }
}