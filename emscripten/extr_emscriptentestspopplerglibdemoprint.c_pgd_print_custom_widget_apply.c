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
struct TYPE_3__ {int /*<<< orphan*/  options; int /*<<< orphan*/  options_combo; } ;
typedef  int /*<<< orphan*/  PgdPrintOptions ;
typedef  TYPE_1__ PgdPrintDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkPrintSettings ;
typedef  int /*<<< orphan*/  GtkPrintOperation ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGD_PRINT_OPTIONS ; 
 int /*<<< orphan*/  gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_print_operation_get_print_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_print_settings_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_print_custom_widget_apply (GtkPrintOperation *op,
                               GtkWidget         *widget,
                               PgdPrintDemo      *demo)
{
        GtkPrintSettings *settings;
        PgdPrintOptions   options;

        settings = gtk_print_operation_get_print_settings (op);
        options = gtk_combo_box_get_active (GTK_COMBO_BOX (demo->options_combo));
        /* Workaround for gtk+ bug, we need to save the options ourselves */
        demo->options = options;
        gtk_print_settings_set_int (settings, PGD_PRINT_OPTIONS, options);
}