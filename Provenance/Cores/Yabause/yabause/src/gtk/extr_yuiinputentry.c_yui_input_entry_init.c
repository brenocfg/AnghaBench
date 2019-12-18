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
typedef  int /*<<< orphan*/  YuiInputEntry ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void yui_input_entry_init(YuiInputEntry *yie) {
	gtk_container_set_border_width(GTK_CONTAINER(yie), 0);
	gtk_table_set_row_spacings(GTK_TABLE(yie), 10);
	gtk_table_set_col_spacings(GTK_TABLE(yie), 10);
}