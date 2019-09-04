#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  doc; int /*<<< orphan*/  treeview; } ;
typedef  int /*<<< orphan*/  PopplerFontsIter ;
typedef  int /*<<< orphan*/  PopplerFontInfo ;
typedef  TYPE_1__ PgdFontsDemo ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FONTS_DETAILS_COLUMN ; 
 int /*<<< orphan*/  FONTS_NAME_COLUMN ; 
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 char* font_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_markup_printf_escaped (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  g_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_events_pending () ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gtk_main_iteration () ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_fonts_update_progress (TYPE_1__*,int,int) ; 
 int poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_font_info_new (int /*<<< orphan*/ ) ; 
 scalar_t__ poppler_font_info_scan (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  poppler_fonts_iter_free (int /*<<< orphan*/ *) ; 
 char* poppler_fonts_iter_get_file_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_fonts_iter_get_font_type (int /*<<< orphan*/ *) ; 
 char* poppler_fonts_iter_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_fonts_iter_is_embedded (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_fonts_iter_is_subset (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_fonts_iter_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
pgd_fonts_fill_model (PgdFontsDemo *demo)
{
	GtkTreeModel     *model;
	PopplerFontInfo  *font_info;
	PopplerFontsIter *fonts_iter;
	gint              n_pages, scanned = 0;

	n_pages = poppler_document_get_n_pages (demo->doc);
	
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (demo->treeview));
	g_object_ref (model);

	gtk_list_store_clear (GTK_LIST_STORE (model));

	font_info = poppler_font_info_new (demo->doc);

	while (poppler_font_info_scan (font_info, 20, &fonts_iter)) {
		pgd_fonts_update_progress (demo, n_pages, scanned);
		
		while (gtk_events_pending ())
			gtk_main_iteration ();

		scanned += 20;
		
		if (!fonts_iter)
			continue;
		
		do {
			GtkTreeIter iter;
			const gchar *name;
			const gchar *type;
			const gchar *embedded;
			const gchar *filename;
			gchar       *details;

			name = poppler_fonts_iter_get_name (fonts_iter);
			if (!name)
				name = "No name";

			type = font_type_to_string (poppler_fonts_iter_get_font_type (fonts_iter));
			
			if (poppler_fonts_iter_is_embedded (fonts_iter)) {
				if (poppler_fonts_iter_is_subset (fonts_iter))
					embedded = "Embedded subset";
				else
					embedded = "Embedded";
			} else {
				embedded = "Not embedded";
			}

			filename = poppler_fonts_iter_get_file_name (fonts_iter);

			if (filename)
				details = g_markup_printf_escaped ("%s\n%s (%s)", type, embedded, filename);
			else
				details = g_markup_printf_escaped ("%s\n%s", type, embedded);

			gtk_list_store_append (GTK_LIST_STORE (model), &iter);
			gtk_list_store_set (GTK_LIST_STORE (model), &iter,
					    FONTS_NAME_COLUMN, name,
					    FONTS_DETAILS_COLUMN, details,
					    -1);
			
			g_free (details);
		} while (poppler_fonts_iter_next (fonts_iter));
		poppler_fonts_iter_free (fonts_iter);
	}

	pgd_fonts_update_progress (demo, n_pages, scanned);
	
	g_object_unref (font_info);
	g_object_unref (model);

	return FALSE;
}