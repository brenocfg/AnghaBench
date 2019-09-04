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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BUTTONBOX_SPREAD ; 
 int /*<<< orphan*/  GTK_BUTTON_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_OBJECT ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  N_COLUMNS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,char*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_button_box_set_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_hbutton_box_new () ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_list_store_new (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_insert_column_with_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_attachments_create_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_attachments_fill_model (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_attachments_save_button_clicked ; 
 int /*<<< orphan*/  pgd_attachments_validate_button_clicked ; 
 scalar_t__ poppler_document_has_attachments (int /*<<< orphan*/ *) ; 

GtkWidget *
pgd_attachments_create_widget (PopplerDocument *document)
{
	GtkWidget    *vbox;
	GtkWidget    *treeview;
	GtkListStore *model;
	GtkWidget    *swindow;
	GtkWidget    *hbox, *button;
	gboolean      has_attachments;

	vbox = gtk_vbox_new (FALSE, 12);

	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	has_attachments = poppler_document_has_attachments (document);
	if (has_attachments) {
		model = gtk_list_store_new (N_COLUMNS,
					    G_TYPE_STRING, G_TYPE_STRING,
					    G_TYPE_STRING,
					    G_TYPE_STRING, G_TYPE_STRING,
					    G_TYPE_OBJECT);
		pgd_attachments_fill_model (model, document);
		treeview = pgd_attachments_create_list (GTK_TREE_MODEL (model));
	} else {
		GtkCellRenderer *renderer;
		GtkTreeIter      iter;
		gchar           *markup;

		model = gtk_list_store_new (1, G_TYPE_STRING);
		gtk_list_store_append (model, &iter);
		markup = g_strdup_printf ("<span size=\"larger\" style=\"italic\">%s</span>",
					  "The document doesn't contain attachments");
		gtk_list_store_set (model, &iter, 0, markup, -1);
		g_free (markup);

		treeview = gtk_tree_view_new_with_model (GTK_TREE_MODEL (model));

		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
							     0, "Name",
							     renderer,
							     "markup", 0,
							     NULL);
	}
	g_object_unref (model);

	gtk_container_add (GTK_CONTAINER (swindow), treeview);
	gtk_widget_show (treeview);

	gtk_box_pack_start (GTK_BOX (vbox), swindow, TRUE, TRUE, 0);
	gtk_widget_show (swindow);

	if (!has_attachments)
		return vbox;
	
	hbox = gtk_hbutton_box_new ();
	gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_SPREAD);

	button = gtk_button_new_with_label ("Save");
	g_signal_connect (G_OBJECT (button), "clicked",
			  G_CALLBACK (pgd_attachments_save_button_clicked),
			  (gpointer)treeview);

	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Validate");
	g_signal_connect (G_OBJECT (button), "clicked",
			  G_CALLBACK (pgd_attachments_validate_button_clicked),
			  (gpointer)treeview);

	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 6);
	gtk_widget_show (hbox);

	return vbox;
}