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
typedef  int /*<<< orphan*/  PopplerAnnotMovie ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_movie_view_new () ; 
 int /*<<< orphan*/  pgd_movie_view_set_movie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_annot_movie_get_movie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_annot_movie_get_title (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_movie (GtkWidget         *table,
				PopplerAnnotMovie *annot,
				gint              *row)
{
    GtkWidget *movie_view;
    gchar *text;

    text = poppler_annot_movie_get_title (annot);
    pgd_table_add_property (GTK_TABLE (table), "<b>Movie Title:</b>", text, row);
    g_free (text);

    movie_view = pgd_movie_view_new ();
    pgd_movie_view_set_movie (movie_view, poppler_annot_movie_get_movie (annot));
    pgd_table_add_property_with_custom_widget (GTK_TABLE (table), "<b>Movie:</b>", movie_view, row);
    gtk_widget_show (movie_view);
}