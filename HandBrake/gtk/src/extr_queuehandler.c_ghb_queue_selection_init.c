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
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_selected_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_box_select_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ghb_queue_selection_init(signal_user_data_t * ud)
{
    GtkListBox    * lb;
    GtkListBoxRow * row;

    lb            = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row           = gtk_list_box_get_selected_row(lb);
    if (row == NULL)
    {
        row = gtk_list_box_get_row_at_index(lb, 0);
        if (row != NULL)
        {
            gtk_list_box_select_row(lb, row);
        }
    }
}