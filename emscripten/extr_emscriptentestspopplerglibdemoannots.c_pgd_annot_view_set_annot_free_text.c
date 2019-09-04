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
typedef  int /*<<< orphan*/  PopplerAnnotFreeText ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_free_text_callout_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_free_text_quadding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_free_text (GtkWidget            *table,
                                    PopplerAnnotFreeText *annot,
                                    gint                 *row)
{
    gchar *text;

    pgd_table_add_property (GTK_TABLE (table), "<b>Quadding:</b>", get_free_text_quadding (annot), row);

    text = get_free_text_callout_line (annot);
    pgd_table_add_property (GTK_TABLE (table), "<b>Callout:</b>", text, row);
    g_free (text);
}