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
 int /*<<< orphan*/  pgd_table_add_property_with_value_widget (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void
pgd_table_add_property (GtkTable    *table,
			const gchar *markup,
			const gchar *value,
			gint        *row)
{
	GtkWidget *label;

	pgd_table_add_property_with_value_widget (table, markup, &label, value, row);
}