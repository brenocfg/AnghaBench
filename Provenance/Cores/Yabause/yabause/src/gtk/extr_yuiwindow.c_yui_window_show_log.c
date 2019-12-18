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
struct TYPE_3__ {int /*<<< orphan*/  logpopup; } ;
typedef  TYPE_1__ YuiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ ) ; 

void yui_window_show_log(YuiWindow * yui) {
	static int i = 0;
	if (i)
		gtk_widget_hide(yui->logpopup);
	else
		gtk_widget_show_all(yui->logpopup);
	i = !i;
}