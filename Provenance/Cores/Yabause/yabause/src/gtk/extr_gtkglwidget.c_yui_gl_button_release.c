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
struct TYPE_3__ {int button; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PERMOUSE ; 
 scalar_t__ PerGetId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerMouseLeftReleased (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerMouseMiddleReleased (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerMouseRightReleased (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padbits ; 

__attribute__((used)) static gboolean yui_gl_button_release(GtkWidget * widget, GdkEventButton * event, gpointer user_data) {
	if (PerGetId(padbits) == PERMOUSE) {
		switch(event->button) {
			case 1:
				PerMouseLeftReleased(padbits);
				break;
			case 2:
				PerMouseMiddleReleased(padbits);
				break;
			case 3:
				PerMouseRightReleased(padbits);
				break;
		}
	}
	return FALSE;
}