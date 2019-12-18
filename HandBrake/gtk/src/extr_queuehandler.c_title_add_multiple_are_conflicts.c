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
struct TYPE_3__ {int /*<<< orphan*/  settings_array; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  title_add_multiple_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  title_multiple_can_select (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static gboolean
title_add_multiple_are_conflicts(signal_user_data_t *ud)
{
    GtkListBox *list;
    GtkWidget *row;
    gint count, ii;

    list = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "title_add_multiple_list"));
    count = ghb_array_len(ud->settings_array);
    for (ii = 0; ii < count; ii++)
    {
        row = GTK_WIDGET(gtk_list_box_get_row_at_index(list, ii));
        if (!title_multiple_can_select(ud->settings_array, ii))
        {
            title_add_multiple_set_sensitive(GTK_WIDGET(row), FALSE);
            return TRUE;
        }
        title_add_multiple_set_sensitive(GTK_WIDGET(row), TRUE);
    }
    return FALSE;
}