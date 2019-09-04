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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  PopplerAnnotScreen ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_action_view_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_action_view_set_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_annot_screen_get_action (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_screen (GtkWidget          *table,
				 PopplerAnnotScreen *annot,
				 gint               *row)
{
    GtkWidget *action_view;

    action_view = pgd_action_view_new (NULL);
    pgd_action_view_set_action (action_view, poppler_annot_screen_get_action (annot));
    pgd_table_add_property_with_custom_widget (GTK_TABLE (table), "<b>Action:</b>", action_view, row);
    gtk_widget_show (action_view);
}