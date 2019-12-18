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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkScale ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  adjustment_configure (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 double gtk_adjustment_get_page_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_range_get_adjustment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_range_set_inverted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_scale_set_digits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_scale_set_draw_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ghb_scale_configure(
    signal_user_data_t *ud,
    char *name,
    double val, double min, double max,
    double step, double page,
    int digits, gboolean inverted)
{
    GtkScale *scale;
    GtkAdjustment *adj;
    double page_sz;

    scale = GTK_SCALE(GHB_WIDGET(ud->builder, name));

    gtk_scale_set_draw_value(scale, FALSE);
    adj = gtk_range_get_adjustment(GTK_RANGE(scale));
    page_sz = gtk_adjustment_get_page_size(adj);

    adjustment_configure(adj, val, min, max, step, page, page_sz);

    gtk_scale_set_digits(scale, digits);
    gtk_range_set_inverted(GTK_RANGE(scale), inverted);
    gtk_scale_set_draw_value(scale, TRUE);
}