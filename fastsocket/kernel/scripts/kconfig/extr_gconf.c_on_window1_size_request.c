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
typedef  int gint ;
struct TYPE_3__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkRequisition ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_PANED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_get_size (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_window_get_default_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  main_wnd ; 
 int /*<<< orphan*/  vpaned ; 

void
on_window1_size_request(GtkWidget * widget,
			GtkRequisition * requisition, gpointer user_data)
{
	static gint old_h;
	gint w, h;

	if (widget->window == NULL)
		gtk_window_get_default_size(GTK_WINDOW(main_wnd), &w, &h);
	else
		gdk_window_get_size(widget->window, &w, &h);

	if (h == old_h)
		return;
	old_h = h;

	gtk_paned_set_position(GTK_PANED(vpaned), 2 * h / 3);
}