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
struct TYPE_3__ {int /*<<< orphan*/  cursor; int /*<<< orphan*/  darea; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GdkCursorType ;
typedef  int /*<<< orphan*/  GdkCursor ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_LAST_CURSOR ; 
 int /*<<< orphan*/ * gdk_cursor_new_for_display (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_cursor_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_flush () ; 
 int /*<<< orphan*/  gdk_window_set_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_selections_update_cursor (PgdSelectionsDemo *demo,
			      GdkCursorType      cursor_type)
{
	GdkWindow *window = gtk_widget_get_window (demo->darea);
	GdkCursor *cursor = NULL;

	if (cursor_type == demo->cursor)
		return;

	if (cursor_type != GDK_LAST_CURSOR) {
		cursor = gdk_cursor_new_for_display (gtk_widget_get_display (demo->darea),
						     cursor_type);
	}

	demo->cursor = cursor_type;

	gdk_window_set_cursor (window, cursor);
	gdk_flush ();
	if (cursor)
		gdk_cursor_unref (cursor);
}