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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabauseInit ; 
 int /*<<< orphan*/  YabauseReset ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yinit ; 
 int /*<<< orphan*/ * yui ; 
 int /*<<< orphan*/  yui_main ; 
 int /*<<< orphan*/ * yui_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GtkWidget * yui_new(void) {
	yui = yui_window_new(NULL, G_CALLBACK(YabauseInit), &yinit, yui_main, G_CALLBACK(YabauseReset));

	gtk_widget_show(yui);

	return yui;
}