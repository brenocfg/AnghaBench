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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTable ;

/* Variables and functions */
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PANGO_ELLIPSIZE_END ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,double,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pgd_table_add_property_with_value_widget (GtkTable    *table,
					  const gchar *markup,
					  GtkWidget  **value_widget,
					  const gchar *value,
					  gint        *row)
{
	GtkWidget *label;

	*value_widget = label = gtk_label_new (value);
	g_object_set (G_OBJECT (label),
		      "xalign", 0.0,
		      "selectable", TRUE,
		      "ellipsize", PANGO_ELLIPSIZE_END,
		      NULL);
	pgd_table_add_property_with_custom_widget (table, markup, label, row);
}