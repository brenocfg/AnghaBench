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
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkListBoxRow *
get_row_before (GtkListBox    * list, GtkListBoxRow * row)
{
    int pos = gtk_list_box_row_get_index(row);
    return gtk_list_box_get_row_at_index(list, pos - 1);
}