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
struct TYPE_3__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_widget (int /*<<< orphan*/ ,char*) ; 
 int ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ghb_queue_progress_set_visible(signal_user_data_t *ud, int index,
                               gboolean visible)
{
    GtkListBox    * lb;
    GtkListBoxRow * row;
    GtkWidget     * progress;

    int count = ghb_array_len(ud->queue);
    if (index < 0 || index >= count)
    {
        // invalid index
        return;
    }

    lb = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row = gtk_list_box_get_row_at_index(lb, index);
    if (row == NULL)
    {
        return;
    }
    progress = find_widget(GTK_WIDGET(row), "queue_item_progress");
    gtk_widget_set_visible(progress, visible);
}