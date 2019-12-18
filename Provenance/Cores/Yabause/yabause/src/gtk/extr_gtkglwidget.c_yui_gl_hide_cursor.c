#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  TYPE_2__ GdkEventMotion ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PERMOUSE ; 
 scalar_t__ PerGetId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerMouseMove (int /*<<< orphan*/ ,double,double) ; 
 int beforehiding ; 
 double g_key_file_get_double (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gdk_window_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gonna_hide ; 
 int /*<<< orphan*/  keyfile ; 
 int oldx ; 
 int oldy ; 
 int /*<<< orphan*/  padbits ; 

__attribute__((used)) static gboolean yui_gl_hide_cursor(GtkWidget * widget, GdkEventMotion * event, gpointer user_data) {
	if (PerGetId(padbits) == PERMOUSE) {
		int x = event->x;
		int y = event->y;
		double speed = g_key_file_get_double(keyfile, "General", "MouseSpeed", NULL);

		PerMouseMove(padbits, speed * (x - oldx), -speed * (y - oldy));
		oldx = x;
		oldy = y;
	}

	if (beforehiding == 0) {
		gdk_window_set_cursor(widget->window, NULL);
		g_timeout_add(1000, gonna_hide, widget);
	}

	beforehiding = 2;

	return FALSE;
}