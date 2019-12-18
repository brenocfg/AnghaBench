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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  keyval; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GdkEventKey ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PerKeyDown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean yui_window_keypress(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	PerKeyDown(event->keyval);

	return FALSE;
}