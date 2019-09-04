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
typedef  char gchar ;
typedef  int /*<<< orphan*/  PopplerAnnotText ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* get_text_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 char* poppler_annot_text_get_icon (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_annot_text_get_is_open (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_text (GtkWidget        *table,
                               PopplerAnnotText *annot,
                               gint             *row)
{
    gchar *text;

    pgd_table_add_property (GTK_TABLE (table), "<b>Is open:</b>",
                            poppler_annot_text_get_is_open (annot) ? "Yes" : "No", row);

    text = poppler_annot_text_get_icon (annot);
    pgd_table_add_property (GTK_TABLE (table), "<b>Icon:</b>", text, row);
    g_free (text);

    pgd_table_add_property (GTK_TABLE (table), "<b>State:</b>", get_text_state (annot), row);
}