#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* gdouble ;
struct TYPE_6__ {int /*<<< orphan*/  doc; int /*<<< orphan*/  num_page; } ;
struct TYPE_5__ {void* y2; void* y1; void* x2; void* x1; } ;
typedef  TYPE_1__ PopplerRectangle ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  int /*<<< orphan*/  PopplerAnnot ;
typedef  TYPE_2__ PgdAnnotsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int GTK_DIALOG_MODAL ; 
 int /*<<< orphan*/  GTK_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_dialog_get_content_area (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_dialog_new_with_buttons (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 void* gtk_spin_button_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_spin_button_new_with_range (int /*<<< orphan*/ ,void*,double) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_toplevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_annot_text_new (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_add_annot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ *,void**,void**) ; 

__attribute__((used)) static void
pgd_annots_add_annot (GtkWidget     *button,
		      PgdAnnotsDemo *demo)
{
    GtkWidget   *hbox, *vbox;
    GtkWidget   *type_selector;
    GtkWidget   *label;
    GtkWidget   *rect_hbox;
    GtkWidget   *rect_x1, *rect_y1, *rect_x2, *rect_y2;
    GtkWidget   *dialog;
    PopplerPage *page;
    gdouble      width, height;
    PopplerAnnot *annot;
    PopplerRectangle rect;

    page = poppler_document_get_page (demo->doc, demo->num_page);
    if (!page)
	    return;
    poppler_page_get_size (page, &width, &height);

    dialog = gtk_dialog_new_with_buttons ("Add new annotation",
					  GTK_WINDOW (gtk_widget_get_toplevel (button)),
					  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  "Add annotation", GTK_RESPONSE_ACCEPT,
					  NULL);

    vbox = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    type_selector = gtk_combo_box_new_text ();
    gtk_combo_box_append_text (GTK_COMBO_BOX (type_selector), "POPPLER_ANNOT_UNKNOWN");
    gtk_combo_box_append_text (GTK_COMBO_BOX (type_selector), "POPPLER_ANNOT_TEXT");
    gtk_combo_box_set_active (GTK_COMBO_BOX (type_selector), 1);
    gtk_box_pack_start (GTK_BOX (vbox), type_selector, TRUE, TRUE, 0);
    gtk_widget_show (type_selector);

    hbox = gtk_hbox_new (FALSE, 6);

    rect_hbox = gtk_hbox_new (FALSE, 6);

    label = gtk_label_new ("x1:");
    gtk_box_pack_start (GTK_BOX (rect_hbox), label, TRUE, TRUE, 0);
    gtk_widget_show (label);

    rect_x1 = gtk_spin_button_new_with_range (0, width, 1.0);
    gtk_box_pack_start (GTK_BOX (rect_hbox), rect_x1, TRUE, TRUE, 0);
    gtk_widget_show (rect_x1);

    gtk_box_pack_start (GTK_BOX (hbox), rect_hbox, FALSE, TRUE, 0);
    gtk_widget_show (rect_hbox);

    rect_hbox = gtk_hbox_new (FALSE, 6);

    label = gtk_label_new ("x2:");
    gtk_box_pack_start (GTK_BOX (rect_hbox), label, TRUE, TRUE, 0);
    gtk_widget_show (label);

    rect_x2 = gtk_spin_button_new_with_range (0, width, 1.0);
    gtk_box_pack_start (GTK_BOX (rect_hbox), rect_x2, TRUE, TRUE, 0);
    gtk_widget_show (rect_x2);

    gtk_box_pack_start (GTK_BOX (hbox), rect_hbox, FALSE, TRUE, 0);
    gtk_widget_show (rect_hbox);

    rect_hbox = gtk_hbox_new (FALSE, 6);

    label = gtk_label_new ("y1:");
    gtk_box_pack_start (GTK_BOX (rect_hbox), label, TRUE, TRUE, 0);
    gtk_widget_show (label);

    rect_y1 = gtk_spin_button_new_with_range (0, height, 1.0);
    gtk_box_pack_start (GTK_BOX (rect_hbox), rect_y1, TRUE, TRUE, 0);
    gtk_widget_show (rect_y1);

    gtk_box_pack_start (GTK_BOX (hbox), rect_hbox, FALSE, TRUE, 0);
    gtk_widget_show (rect_hbox);

    rect_hbox = gtk_hbox_new (FALSE, 6);

    label = gtk_label_new ("y2:");
    gtk_box_pack_start (GTK_BOX (rect_hbox), label, TRUE, TRUE, 0);
    gtk_widget_show (label);

    rect_y2 = gtk_spin_button_new_with_range (0, height, 1.0);
    gtk_box_pack_start (GTK_BOX (rect_hbox), rect_y2, TRUE, TRUE, 0);
    gtk_widget_show (rect_y2);

    gtk_box_pack_start (GTK_BOX (hbox), rect_hbox, FALSE, TRUE, 0);
    gtk_widget_show (rect_hbox);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
    gtk_widget_show (hbox);

    gtk_dialog_run (GTK_DIALOG (dialog));

    rect.x1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (rect_x1));
    rect.x2 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (rect_x2));
    rect.y1 = height - gtk_spin_button_get_value (GTK_SPIN_BUTTON (rect_y2));
    rect.y2 = height - gtk_spin_button_get_value (GTK_SPIN_BUTTON (rect_y1));
    annot = poppler_annot_text_new (demo->doc, &rect);
    poppler_page_add_annot (page, annot);

    g_object_unref (page);

    gtk_widget_destroy (dialog);
}