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
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_adjustment_configure (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 

__attribute__((used)) static void
adjustment_configure(
    GtkAdjustment *adj,
    double val,
    double min, double max,
    double step, double page, double page_sz)
{
    gtk_adjustment_configure(adj, val, min, max, step, page, page_sz);
}