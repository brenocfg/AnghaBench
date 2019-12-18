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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_wnd ; 
 int /*<<< orphan*/  on_window1_delete_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void on_quit1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (!on_window1_delete_event(NULL, NULL, NULL))
		gtk_widget_destroy(GTK_WIDGET(main_wnd));
}