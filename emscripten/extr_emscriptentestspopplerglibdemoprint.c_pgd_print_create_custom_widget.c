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
struct TYPE_3__ {int /*<<< orphan*/ * options_combo; } ;
typedef  int /*<<< orphan*/  PgdPrintOptions ;
typedef  TYPE_1__ PgdPrintDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkPrintSettings ;
typedef  int /*<<< orphan*/  GtkPrintOperation ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGD_PRINT_OPTIONS ; 
 int /*<<< orphan*/  PRINT_DOCUMENT_MARKUPS ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 int /*<<< orphan*/ * gtk_print_operation_get_print_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_print_settings_get_int_with_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GObject *
pgd_print_create_custom_widget (GtkPrintOperation *op,
                                PgdPrintDemo      *demo)
{
        GtkWidget        *hbox;
        GtkWidget        *label, *combo;
        GtkPrintSettings *settings;
        PgdPrintOptions   options;

        settings = gtk_print_operation_get_print_settings (op);
        options = gtk_print_settings_get_int_with_default (settings,
                                                           PGD_PRINT_OPTIONS,
                                                           PRINT_DOCUMENT_MARKUPS);

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (hbox), 12);

        label = gtk_label_new ("Print: ");
        gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
        gtk_widget_show (label);

        combo = gtk_combo_box_new_text ();
        demo->options_combo = combo;
        gtk_combo_box_append_text (GTK_COMBO_BOX (combo), "Document");
        gtk_combo_box_append_text (GTK_COMBO_BOX (combo), "Document and markup");
        gtk_combo_box_append_text (GTK_COMBO_BOX (combo), "Document and stamps");
        gtk_combo_box_set_active (GTK_COMBO_BOX (combo), options);
        gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, FALSE, 0);
        gtk_widget_show (combo);

        return G_OBJECT (hbox);
}