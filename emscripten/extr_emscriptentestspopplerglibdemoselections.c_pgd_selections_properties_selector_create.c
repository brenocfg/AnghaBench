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
typedef  int /*<<< orphan*/  gpointer ;
typedef  double gint ;
typedef  char gchar ;
struct TYPE_3__ {int /*<<< orphan*/ * bg_color_button; int /*<<< orphan*/ * fg_color_button; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,double) ; 
 int /*<<< orphan*/  gtk_box_pack_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 void* gtk_color_button_new () ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 int /*<<< orphan*/ * gtk_spin_button_new_with_range (int,double,double) ; 
 int /*<<< orphan*/  gtk_spin_button_set_value (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_selections_bg_color_changed ; 
 int /*<<< orphan*/  pgd_selections_fg_color_changed ; 
 int /*<<< orphan*/  pgd_selections_page_selector_value_changed ; 
 int /*<<< orphan*/  pgd_selections_render ; 
 int /*<<< orphan*/  pgd_selections_scale_selector_value_changed ; 
 double poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 

GtkWidget *
pgd_selections_properties_selector_create (PgdSelectionsDemo *demo)
{
	GtkWidget *hbox, *vbox;
	GtkWidget *label;
	GtkWidget *page_hbox, *page_selector;
	GtkWidget *scale_hbox, *scale_selector;
	GtkWidget *rotate_hbox, *rotate_selector;
	GtkWidget *color_hbox;
	GtkWidget *button;
	gint       n_pages;
	gchar     *str;

	n_pages = poppler_document_get_n_pages (demo->doc);

	vbox = gtk_vbox_new (FALSE, 6);

	hbox = gtk_hbox_new (FALSE, 12);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
	gtk_widget_show (hbox);

	page_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Page:");
	gtk_box_pack_start (GTK_BOX (page_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	page_selector = gtk_spin_button_new_with_range (1, n_pages, 1);
	g_signal_connect (G_OBJECT (page_selector), "value-changed",
			  G_CALLBACK (pgd_selections_page_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (page_hbox), page_selector, TRUE, TRUE, 0);
	gtk_widget_show (page_selector);

	str = g_strdup_printf ("of %d", n_pages);
	label = gtk_label_new (str);
	gtk_box_pack_start (GTK_BOX (page_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);
	g_free (str);

	gtk_box_pack_start (GTK_BOX (hbox), page_hbox, FALSE, TRUE, 0);
	gtk_widget_show (page_hbox);

	scale_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Scale:");
	gtk_box_pack_start (GTK_BOX (scale_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	scale_selector = gtk_spin_button_new_with_range (0, 10.0, 0.1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (scale_selector), 1.0);
	g_signal_connect (G_OBJECT (scale_selector), "value-changed",
			  G_CALLBACK (pgd_selections_scale_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (scale_hbox), scale_selector, TRUE, TRUE, 0);
	gtk_widget_show (scale_selector);

	gtk_box_pack_start (GTK_BOX (hbox), scale_hbox, FALSE, TRUE, 0);
	gtk_widget_show (scale_hbox);

	rotate_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Rotate:");
	gtk_box_pack_start (GTK_BOX (rotate_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	rotate_selector = gtk_combo_box_new_text ();
	gtk_combo_box_append_text (GTK_COMBO_BOX (rotate_selector), "0");
	gtk_combo_box_append_text (GTK_COMBO_BOX (rotate_selector), "90");
	gtk_combo_box_append_text (GTK_COMBO_BOX (rotate_selector), "180");
	gtk_combo_box_append_text (GTK_COMBO_BOX (rotate_selector), "270");
	gtk_combo_box_set_active (GTK_COMBO_BOX (rotate_selector), 0);
#if 0
	g_signal_connect (G_OBJECT (rotate_selector), "changed",
			  G_CALLBACK (pgd_selections_rotate_selector_changed),
			  (gpointer)demo);
#endif
	gtk_box_pack_start (GTK_BOX (rotate_hbox), rotate_selector, TRUE, TRUE, 0);
	gtk_widget_show (rotate_selector);

	gtk_box_pack_start (GTK_BOX (hbox), rotate_hbox, FALSE, TRUE, 0);
	gtk_widget_show (rotate_hbox);

	hbox = gtk_hbox_new (FALSE, 12);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
	gtk_widget_show (hbox);

	color_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Foreground Color:");
	gtk_box_pack_start (GTK_BOX (color_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->fg_color_button = gtk_color_button_new ();
	g_signal_connect (demo->fg_color_button, "notify::color",
			  G_CALLBACK (pgd_selections_fg_color_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (color_hbox), demo->fg_color_button, TRUE, TRUE, 0);
	gtk_widget_show (demo->fg_color_button);

	gtk_box_pack_start (GTK_BOX (hbox), color_hbox, FALSE, TRUE, 0);
	gtk_widget_show (color_hbox);

	color_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Background Color:");
	gtk_box_pack_start (GTK_BOX (color_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->bg_color_button = gtk_color_button_new ();
	g_signal_connect (demo->bg_color_button, "notify::color",
			  G_CALLBACK (pgd_selections_bg_color_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (color_hbox), demo->bg_color_button, TRUE, TRUE, 0);
	gtk_widget_show (demo->bg_color_button);

	gtk_box_pack_start (GTK_BOX (hbox), color_hbox, FALSE, TRUE, 0);
	gtk_widget_show (color_hbox);

	button = gtk_button_new_with_label ("Render");
	g_signal_connect (G_OBJECT (button), "clicked",
			  G_CALLBACK (pgd_selections_render),
			  (gpointer)demo);
	gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, TRUE, 0);
	gtk_widget_show (button);

	return vbox;
}