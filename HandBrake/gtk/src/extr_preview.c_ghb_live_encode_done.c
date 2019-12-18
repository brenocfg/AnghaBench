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
struct TYPE_6__ {TYPE_1__* preview; int /*<<< orphan*/  builder; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  scalar_t__ gboolean ;
struct TYPE_5__ {int live_id; size_t encode_frame; size_t frame; int /*<<< orphan*/ * encoded; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_progress_bar_set_fraction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  live_preview_start (TYPE_2__*) ; 

void
ghb_live_encode_done(signal_user_data_t *ud, gboolean success)
{
    GtkWidget *widget;
    GtkWidget *prog;

    ud->preview->live_id = -1;
    prog = GHB_WIDGET(ud->builder, "live_encode_progress");
    if (success &&
        ud->preview->encode_frame == ud->preview->frame)
    {
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(prog), "Done");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(prog), 1);
        ud->preview->encoded[ud->preview->encode_frame] = TRUE;
#if defined(_ENABLE_GST)
        live_preview_start(ud);
#endif
        widget = GHB_WIDGET(ud->builder, "live_progress_box");
        gtk_widget_hide (widget);
        widget = GHB_WIDGET(ud->builder, "live_preview_progress");
        gtk_widget_show (widget);
    }
    else
    {
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(prog), "");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(prog), 0);
        ud->preview->encoded[ud->preview->encode_frame] = FALSE;
    }
}