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
typedef  int /*<<< orphan*/  PopplerMovie ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_STOCK_MEDIA_PLAY ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_alignment_new (double,double,int,int) ; 
 int /*<<< orphan*/  gtk_alignment_set_padding (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/ * gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_from_stock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_movie_view_play_movie ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* poppler_movie_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_movie_need_poster (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_movie_show_controls (int /*<<< orphan*/ *) ; 

void
pgd_movie_view_set_movie (GtkWidget    *movie_view,
			  PopplerMovie *movie)
{
	GtkWidget  *alignment;
	GtkWidget  *table;
	GtkWidget  *button;
	gint        row = 0;

	alignment = gtk_bin_get_child (GTK_BIN (movie_view));
	if (alignment) {
		gtk_container_remove (GTK_CONTAINER (movie_view), alignment);
	}

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 12, 5);
	gtk_container_add (GTK_CONTAINER (movie_view), alignment);
	gtk_widget_show (alignment);

	if (!movie)
		return;

	table = gtk_table_new (10, 2, FALSE);
	gtk_table_set_col_spacings (GTK_TABLE (table), 6);
	gtk_table_set_row_spacings (GTK_TABLE (table), 6);

	pgd_table_add_property (GTK_TABLE (table), "<b>Filename:</b>", poppler_movie_get_filename (movie), &row);
	pgd_table_add_property (GTK_TABLE (table), "<b>Need Poster:</b>", poppler_movie_need_poster (movie) ? "Yes" : "No", &row);
	pgd_table_add_property (GTK_TABLE (table), "<b>Show Controls:</b>", poppler_movie_show_controls (movie) ? "Yes" : "No", &row);

	button = gtk_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
	g_signal_connect (button, "clicked",
			  G_CALLBACK (pgd_movie_view_play_movie),
			  movie);
	pgd_table_add_property_with_custom_widget (GTK_TABLE (table), NULL, button, &row);
	gtk_widget_show (button);

	gtk_container_add (GTK_CONTAINER (alignment), table);
	gtk_widget_show (table);
}