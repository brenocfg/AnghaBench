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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_LIST_BOX_ROW (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_TYPE_LIST_BOX_ROW ; 
 scalar_t__ G_OBJECT_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_widget_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkListBoxRow*
list_box_get_row(GtkWidget *widget)
{
    while (widget != NULL && G_OBJECT_TYPE(widget) != GTK_TYPE_LIST_BOX_ROW)
    {
        widget = gtk_widget_get_parent(widget);
    }
    return GTK_LIST_BOX_ROW(widget);
}