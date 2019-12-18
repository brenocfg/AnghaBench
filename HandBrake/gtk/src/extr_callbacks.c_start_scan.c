#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  prefs; int /*<<< orphan*/  builder; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_8__ {TYPE_1__ scan; } ;
typedef  TYPE_3__ ghb_status_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GHB_STATE_IDLE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_TOOL_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TOOL_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ghb_backend_scan (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 long ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_get_status (TYPE_3__*) ; 
 int /*<<< orphan*/  gtk_tool_button_set_icon_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_tool_button_set_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tool_item_set_tooltip_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_scan(
    signal_user_data_t *ud,
    const gchar *path,
    gint title_id,
    gint preview_count)
{
    GtkWidget *widget;
    ghb_status_t status;

    ghb_get_status(&status);
    if (status.scan.state != GHB_STATE_IDLE)
        return;

    widget = GHB_WIDGET(ud->builder, "sourcetoolbutton");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(widget), "hb-stop");
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(widget), _("Stop Scan"));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(widget), _("Stop Scan"));

    widget = GHB_WIDGET(ud->builder, "source_open");
    gtk_widget_set_sensitive(widget, FALSE);
    widget = GHB_WIDGET(ud->builder, "source_title_open");
    gtk_widget_set_sensitive(widget, FALSE);
    ghb_backend_scan(path, title_id, preview_count,
            90000L * ghb_dict_get_int(ud->prefs, "MinTitleDuration"));
}