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
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static GtkListBoxRow *
get_last_row(GtkListBox * list)
{
    int i;
    GtkListBoxRow * row;

    row = NULL;
    for (i = 0; ; i++)
    {
        GtkListBoxRow * tmp;
        tmp = gtk_list_box_get_row_at_index(list, i);
        if (tmp == NULL)
            return row;
        row = tmp;
    }
    return row;
}