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
typedef  int /*<<< orphan*/  gpointer ;
typedef  double gint ;
typedef  char gchar ;
struct TYPE_4__ {int /*<<< orphan*/ * timer_label; int /*<<< orphan*/ * slice_h; int /*<<< orphan*/ * slice_w; int /*<<< orphan*/ * slice_y; int /*<<< orphan*/ * slice_x; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,double) ; 
 int /*<<< orphan*/  gtk_box_pack_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/ * gtk_check_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 void* gtk_label_new (char*) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 void* gtk_spin_button_new_with_range (int,double,double) ; 
 int /*<<< orphan*/  gtk_spin_button_set_value (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_render_mode_selector_changed ; 
 int /*<<< orphan*/  pgd_render_page_selector_value_changed ; 
 int /*<<< orphan*/  pgd_render_printing_selector_changed ; 
 int /*<<< orphan*/  pgd_render_rotate_selector_changed ; 
 int /*<<< orphan*/  pgd_render_scale_selector_value_changed ; 
 int /*<<< orphan*/  pgd_render_slice_selector_setup (TYPE_1__*) ; 
 int /*<<< orphan*/  pgd_render_slice_selector_value_changed ; 
 int /*<<< orphan*/  pgd_render_start ; 
 double poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 

GtkWidget *
pgd_render_properties_selector_create (PgdRenderDemo *demo)
{
	GtkWidget *hbox, *vbox;
	GtkWidget *label;
	GtkWidget *page_hbox, *page_selector;
	GtkWidget *scale_hbox, *scale_selector;
	GtkWidget *rotate_hbox, *rotate_selector;
	GtkWidget *mode_hbox, *mode_selector;
	GtkWidget *printing_selector;
	GtkWidget *slice_hbox, *slice_selector;
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
			  G_CALLBACK (pgd_render_page_selector_value_changed),
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
			  G_CALLBACK (pgd_render_scale_selector_value_changed),
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
	g_signal_connect (G_OBJECT (rotate_selector), "changed",
			  G_CALLBACK (pgd_render_rotate_selector_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (rotate_hbox), rotate_selector, TRUE, TRUE, 0);
	gtk_widget_show (rotate_selector);

	gtk_box_pack_start (GTK_BOX (hbox), rotate_hbox, FALSE, TRUE, 0);
	gtk_widget_show (rotate_hbox);

	mode_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Mode:");
	gtk_box_pack_start (GTK_BOX (mode_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	mode_selector = gtk_combo_box_new_text ();
	gtk_combo_box_append_text (GTK_COMBO_BOX (mode_selector), "cairo");
#ifdef POPPLER_WITH_GDK
	gtk_combo_box_append_text (GTK_COMBO_BOX (mode_selector), "pixbuf");
#endif
	gtk_combo_box_set_active (GTK_COMBO_BOX (mode_selector), 0);
	g_signal_connect (G_OBJECT (mode_selector), "changed",
			  G_CALLBACK (pgd_render_mode_selector_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (mode_hbox), mode_selector, TRUE, TRUE, 0);
	gtk_widget_show (mode_selector);

	gtk_box_pack_start (GTK_BOX (hbox), mode_hbox, FALSE, TRUE, 0);
	gtk_widget_show (mode_hbox);

	printing_selector = gtk_check_button_new_with_label ("Printing");
	g_signal_connect (printing_selector, "toggled",
			  G_CALLBACK (pgd_render_printing_selector_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (hbox), printing_selector, FALSE, TRUE, 0);
	gtk_widget_show (printing_selector);

	hbox = gtk_hbox_new (FALSE, 12);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
	gtk_widget_show (hbox);

	slice_hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("x:");
	gtk_box_pack_start (GTK_BOX (slice_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->slice_x = gtk_spin_button_new_with_range (0, 0, 1.0);
	g_signal_connect (G_OBJECT (demo->slice_x), "value-changed",
			  G_CALLBACK (pgd_render_slice_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (slice_hbox), demo->slice_x, TRUE, TRUE, 0);
	gtk_widget_show (demo->slice_x);

	gtk_box_pack_start (GTK_BOX (hbox), slice_hbox, FALSE, TRUE, 0);
	gtk_widget_show (slice_hbox);

	slice_hbox = gtk_hbox_new (FALSE, 6);
	
	label = gtk_label_new ("y:");
	gtk_box_pack_start (GTK_BOX (slice_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->slice_y = gtk_spin_button_new_with_range (0, 0, 1.0);
	g_signal_connect (G_OBJECT (demo->slice_y), "value-changed",
			  G_CALLBACK (pgd_render_slice_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (slice_hbox), demo->slice_y, TRUE, TRUE, 0);
	gtk_widget_show (demo->slice_y);

	gtk_box_pack_start (GTK_BOX (hbox), slice_hbox, FALSE, TRUE, 0);
	gtk_widget_show (slice_hbox);
	
	slice_hbox = gtk_hbox_new (FALSE, 6);
	
	label = gtk_label_new ("width:");
	gtk_box_pack_start (GTK_BOX (slice_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->slice_w = gtk_spin_button_new_with_range (0, 0, 1.0);
	g_signal_connect (G_OBJECT (demo->slice_w), "value-changed",
			  G_CALLBACK (pgd_render_slice_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (slice_hbox), demo->slice_w, TRUE, TRUE, 0);
	gtk_widget_show (demo->slice_w);

	gtk_box_pack_start (GTK_BOX (hbox), slice_hbox, FALSE, TRUE, 0);
	gtk_widget_show (slice_hbox);
	
	slice_hbox = gtk_hbox_new (FALSE, 6);
	
	label = gtk_label_new ("height:");
	gtk_box_pack_start (GTK_BOX (slice_hbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	demo->slice_h = gtk_spin_button_new_with_range (0, 0, 1.0);
	g_signal_connect (G_OBJECT (demo->slice_h), "value-changed",
			  G_CALLBACK (pgd_render_slice_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (slice_hbox), demo->slice_h, TRUE, TRUE, 0);
	gtk_widget_show (demo->slice_h);

	gtk_box_pack_start (GTK_BOX (hbox), slice_hbox, FALSE, TRUE, 0);
	gtk_widget_show (slice_hbox);

	pgd_render_slice_selector_setup (demo);

	button = gtk_button_new_with_label ("Render");
	g_signal_connect (G_OBJECT (button), "clicked",
			  G_CALLBACK (pgd_render_start),
			  (gpointer)demo);
	gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, TRUE, 0);
	gtk_widget_show (button);

	demo->timer_label = gtk_label_new (NULL);
	gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No page rendered</i>");
	g_object_set (G_OBJECT (demo->timer_label), "xalign", 1.0, NULL);
	gtk_box_pack_end (GTK_BOX (vbox), demo->timer_label, FALSE, TRUE, 0);
	gtk_widget_show (demo->timer_label);

	return vbox;
}