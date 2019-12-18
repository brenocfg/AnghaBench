#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_selected_row (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_update_stats (int /*<<< orphan*/ *,TYPE_1__*) ; 

void queue_update_current_stats(signal_user_data_t * ud)
{
    GtkListBox    * lb;
    GtkListBoxRow * row;
    gint            index;
    GhbValue      * queueDict;

    lb  = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row = gtk_list_box_get_selected_row(lb);
    if (row != NULL)
    {
        // There is a queue list row selected
        index = gtk_list_box_row_get_index(row);
        if (index < 0 || index >= ghb_array_len(ud->queue))
        { // Should never happen
            return;
        }
        queueDict = ghb_array_get(ud->queue, index);
        queue_update_stats(queueDict, ud);
    }
}