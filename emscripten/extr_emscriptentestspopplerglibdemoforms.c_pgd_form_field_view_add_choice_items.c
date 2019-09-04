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
typedef  scalar_t__ gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  PopplerFormField ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTextBuffer ;
typedef  int /*<<< orphan*/  GtkTable ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILL ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TEXT_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_buffer_insert_at_cursor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_text_view_get_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_text_view_new () ; 
 int /*<<< orphan*/  gtk_text_view_set_editable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 char* poppler_form_field_choice_get_item (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ poppler_form_field_choice_get_n_items (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_form_field_choice_is_item_selected (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
pgd_form_field_view_add_choice_items (GtkTable         *table,
				      PopplerFormField *field,
				      gint             *selected,
				      gint             *row)
{
	GtkWidget     *label;
	GtkWidget     *textview, *swindow;
	GtkTextBuffer *buffer;
	gint           i;

	label = gtk_label_new (NULL);
	g_object_set (G_OBJECT (label), "xalign", 0.0, NULL);
	gtk_label_set_markup (GTK_LABEL (label), "<b>Items:</b>");
	gtk_table_attach (GTK_TABLE (table), label, 0, 1, *row, *row + 1,
			  GTK_FILL, GTK_FILL, 0, 0);
	gtk_widget_show (label);

	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC,
					GTK_POLICY_AUTOMATIC);

	textview = gtk_text_view_new ();
	gtk_text_view_set_editable (GTK_TEXT_VIEW (textview), FALSE);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	
	for (i = 0; i < poppler_form_field_choice_get_n_items (field); i++) {
		gchar *item;

		item = poppler_form_field_choice_get_item (field, i);
		gtk_text_buffer_insert_at_cursor (buffer, item, strlen (item));
		gtk_text_buffer_insert_at_cursor (buffer, "\n", strlen ("\n"));
		g_free (item);
		
		if (poppler_form_field_choice_is_item_selected (field, i))
			*selected = i;
	}

	gtk_container_add (GTK_CONTAINER (swindow), textview);
	gtk_widget_show (textview);
	
	gtk_table_attach (GTK_TABLE (table), swindow, 1, 2, *row, *row + 1,
			  GTK_FILL, GTK_FILL, 0, 0);
	gtk_widget_show (swindow); 
	
	*row += 1;
}