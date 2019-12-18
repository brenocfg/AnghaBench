#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  menu; int /*<<< orphan*/  action_group; } ;
typedef  TYPE_2__ YuiWindow ;
struct TYPE_7__ {unsigned int width; unsigned int height; } ;
struct TYPE_9__ {TYPE_1__ allocation; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkAction ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_ACTION (int /*<<< orphan*/ *) ; 
 TYPE_5__* GTK_WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_2__*) ; 
 int /*<<< orphan*/ * gtk_action_group_get_action (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gtk_toggle_action_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_fullscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_resize (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gtk_window_unfullscreen (int /*<<< orphan*/ ) ; 

void yui_window_toggle_fullscreen(GtkWidget * w, YuiWindow * yui) {
	GtkAction * action = gtk_action_group_get_action(yui->action_group, "fullscreen");
	static unsigned int beforefswidth = 1;
	static unsigned int beforefsheight = 1;

	if (gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action))) {
		beforefswidth = GTK_WIDGET(yui)->allocation.width;
		beforefsheight = GTK_WIDGET(yui)->allocation.height;
		gtk_widget_hide(yui->menu);
		gtk_window_fullscreen(GTK_WINDOW(yui));
	} else {
		gtk_window_unfullscreen(GTK_WINDOW(yui));
		gtk_widget_show(yui->menu);
		gtk_window_resize(GTK_WINDOW(yui), beforefswidth, beforefsheight);
	}
}