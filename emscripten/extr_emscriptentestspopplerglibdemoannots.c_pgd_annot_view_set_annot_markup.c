#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
struct TYPE_3__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
typedef  TYPE_1__ PopplerRectangle ;
typedef  int /*<<< orphan*/  PopplerAnnotMarkup ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,...) ; 
 char* get_markup_date (int /*<<< orphan*/ *) ; 
 char* get_markup_external_data (int /*<<< orphan*/ *) ; 
 char* get_markup_reply_to (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 char* poppler_annot_markup_get_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_annot_markup_get_opacity (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_annot_markup_get_popup_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_annot_markup_get_popup_rectangle (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* poppler_annot_markup_get_subject (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_annot_markup_has_popup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_markup (GtkWidget          *table,
                                 PopplerAnnotMarkup *markup,
                                 gint               *row)
{
    gchar *text;
    PopplerRectangle rect;

    text = poppler_annot_markup_get_label (markup);
    pgd_table_add_property (GTK_TABLE (table), "<b>Label:</b>", text, row);
    g_free (text);

    if (poppler_annot_markup_has_popup (markup)) {
	    pgd_table_add_property (GTK_TABLE (table), "<b>Popup is open:</b>",
				    poppler_annot_markup_get_popup_is_open (markup) ? "Yes" : "No", row);

	    poppler_annot_markup_get_popup_rectangle (markup, &rect);
	    text = g_strdup_printf ("X1: %.2f, Y1: %.2f, X2: %.2f, Y2: %.2f",
				    rect.x1, rect.y1, rect.x2, rect.y2);
	    pgd_table_add_property (GTK_TABLE (table), "<b>Popup Rectangle:</b>", text, row);
	    g_free (text);
    }

    text = g_strdup_printf ("%f", poppler_annot_markup_get_opacity (markup));
    pgd_table_add_property (GTK_TABLE (table), "<b>Opacity:</b>", text, row);
    g_free (text);

    text = get_markup_date (markup);
    pgd_table_add_property (GTK_TABLE (table), "<b>Date:</b>", text, row);
    g_free (text);

    text = poppler_annot_markup_get_subject (markup);
    pgd_table_add_property (GTK_TABLE (table), "<b>Subject:</b>", text, row);
    g_free (text);

    pgd_table_add_property (GTK_TABLE (table), "<b>Reply To:</b>", get_markup_reply_to (markup), row);

    pgd_table_add_property (GTK_TABLE (table), "<b>External Data:</b>", get_markup_external_data (markup), row);
}