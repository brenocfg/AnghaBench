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
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  char gchar ;
struct TYPE_3__ {int /*<<< orphan*/ * darea; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ PgdLayersDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_drawing_area_new () ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 int /*<<< orphan*/  gtk_scrolled_window_add_with_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_spin_button_new_with_range (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_layers_page_selector_value_changed ; 
 int /*<<< orphan*/  pgd_layers_viewer_drawing_area_expose ; 
 int /*<<< orphan*/  poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GtkWidget *
pgd_layers_create_viewer (PgdLayersDemo *demo)
{
	GtkWidget *vbox, *hbox;
	GtkWidget *label;
	GtkWidget *swindow;
	GtkWidget *page_selector;
	guint      n_pages;
	gchar     *str;

	vbox = gtk_vbox_new (FALSE, 6);

	hbox = gtk_hbox_new (FALSE, 6);

	label = gtk_label_new ("Page:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
	gtk_widget_show (label);

	n_pages = poppler_document_get_n_pages (demo->doc);
	page_selector = gtk_spin_button_new_with_range (1, n_pages, 1);
	g_signal_connect (G_OBJECT (page_selector), "value-changed",
			  G_CALLBACK (pgd_layers_page_selector_value_changed),
			  (gpointer)demo);
	gtk_box_pack_start (GTK_BOX (hbox), page_selector, FALSE, TRUE, 0);
	gtk_widget_show (page_selector);

	str = g_strdup_printf ("of %d", n_pages);
	label = gtk_label_new (str);
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
	gtk_widget_show (label);
	g_free (str);

	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);
	gtk_widget_show (hbox);

	demo->darea = gtk_drawing_area_new ();
	g_signal_connect (G_OBJECT (demo->darea), "expose_event",
			  G_CALLBACK (pgd_layers_viewer_drawing_area_expose),
			  (gpointer)demo);

	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swindow), demo->darea);
	gtk_widget_show (demo->darea);

	gtk_box_pack_start (GTK_BOX (vbox), swindow, TRUE, TRUE, 0);
	gtk_widget_show (swindow);

	return vbox;
}