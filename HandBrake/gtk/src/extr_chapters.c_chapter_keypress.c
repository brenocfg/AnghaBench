#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDK_KEY_Down ; 
 scalar_t__ GDK_KEY_Return ; 
 scalar_t__ GDK_KEY_Up ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * find_widget (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int) ; 
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_grab_focus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_box_get_row (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
chapter_keypress(
    GtkWidget          * widget,
    guint                keyval,
    signal_user_data_t * ud)
{
    GtkWidget     * entry;
    GtkListBoxRow * row;
    GtkListBox    * lb;
    int             index;

    if (keyval != GDK_KEY_Return &&
        keyval != GDK_KEY_Down &&
        keyval != GDK_KEY_Up)
    {
        return FALSE;
    }

    row    = list_box_get_row(widget);
    lb     = GTK_LIST_BOX(gtk_widget_get_parent(GTK_WIDGET(row)));
    index  = gtk_list_box_row_get_index(row);
    if (keyval == GDK_KEY_Return || keyval == GDK_KEY_Down)
    {
        index++;
    }
    else if (keyval == GDK_KEY_Up && index > 0)
    {
        index--;
    }
    if (index >= 0)
    {
        row = gtk_list_box_get_row_at_index(lb, index);
        if (row != NULL)
        {
            entry  = find_widget(GTK_WIDGET(row), "chapter_entry");
            if (entry != NULL)
            {
                gtk_widget_grab_focus(entry);
                return TRUE;
            }
        }
    }
    return FALSE;
}