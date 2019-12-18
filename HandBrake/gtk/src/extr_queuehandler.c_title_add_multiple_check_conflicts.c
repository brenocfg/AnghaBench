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
struct TYPE_4__ {int /*<<< orphan*/  settings_array; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkToggleButton ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_TOGGLE_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_widget (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  title_add_multiple_set_conflict_label (TYPE_1__*,int) ; 
 int /*<<< orphan*/  title_add_multiple_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int title_multiple_can_select (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
title_add_multiple_check_conflicts(signal_user_data_t *ud)
{
    gint count, ii;
    GhbValue *settings;
    GtkWidget *row;
    GtkListBox *list;
    GtkToggleButton *selected;
    gboolean can_select;
    gboolean are_conflicts = FALSE;

    list = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "title_add_multiple_list"));
    count = ghb_array_len(ud->settings_array);
    for (ii = 0; ii < count; ii++)
    {
        row = GTK_WIDGET(gtk_list_box_get_row_at_index(list, ii));
        selected = GTK_TOGGLE_BUTTON(find_widget(row, "title_selected"));

        settings = ghb_array_get(ud->settings_array, ii);
        can_select = title_multiple_can_select(ud->settings_array, ii);
        ghb_dict_set_bool(settings, "title_selected", FALSE);
        gtk_toggle_button_set_active(selected, FALSE);
        title_add_multiple_set_sensitive(GTK_WIDGET(row), can_select);
        are_conflicts |= !can_select;
    }
    title_add_multiple_set_conflict_label(ud, are_conflicts);
}