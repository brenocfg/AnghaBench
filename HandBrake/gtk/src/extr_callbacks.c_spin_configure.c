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
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkSpinButton ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_SPIN_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjustment_configure (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 double gtk_adjustment_get_page_increment (int /*<<< orphan*/ *) ; 
 double gtk_adjustment_get_page_size (int /*<<< orphan*/ *) ; 
 double gtk_adjustment_get_step_increment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_spin_button_get_adjustment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spin_configure(signal_user_data_t *ud, char *name, double val, double min, double max)
{
    GtkSpinButton *spin;
    GtkAdjustment *adj;
    double step, page, page_sz;

    spin = GTK_SPIN_BUTTON(GHB_WIDGET(ud->builder, name));

    adj = gtk_spin_button_get_adjustment(spin);
    step = gtk_adjustment_get_step_increment(adj);
    page = gtk_adjustment_get_page_increment(adj);
    page_sz = gtk_adjustment_get_page_size(adj);

    adjustment_configure(adj, val, min, max, step, page, page_sz);
}