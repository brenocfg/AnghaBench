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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkProgressBar ;
typedef  int /*<<< orphan*/  GtkLabel ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_PROGRESS_BAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_fraction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_scan_progress(signal_user_data_t *ud)
{
    GtkWidget      * widget;
    GtkProgressBar * progress;
    GtkLabel       * label;

    widget = GHB_WIDGET(ud->builder, "SourceInfoBox");
    gtk_widget_hide(widget);

    widget = GHB_WIDGET(ud->builder, "SourceScanBox");
    gtk_widget_show(widget);

    progress = GTK_PROGRESS_BAR(GHB_WIDGET(ud->builder, "scan_prog"));
    gtk_progress_bar_set_fraction(progress, 0);

    label = GTK_LABEL(GHB_WIDGET(ud->builder, "source_scan_label"));
    gtk_label_set_text( label, _("Scanning ...") );

}