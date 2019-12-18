#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  area; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  int /*<<< orphan*/  YuiScreenshot ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YUI_GL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * YUI_SCREENSHOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 TYPE_1__* yui ; 
 int /*<<< orphan*/  yui_gl_dump_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_screenshot_draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_screenshot_get_type () ; 

GtkWidget * yui_screenshot_new(YuiWindow * y) {
	GtkWidget * dialog;
	YuiScreenshot * yv;

	yui = y;

	dialog = GTK_WIDGET(g_object_new(yui_screenshot_get_type(), NULL));
	yv = YUI_SCREENSHOT(dialog);

	gtk_widget_show_all(dialog);
       
	yui_gl_dump_screen(YUI_GL(yui->area));
	yui_screenshot_draw(yv);

	return dialog;
}