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
struct TYPE_3__ {int /*<<< orphan*/ * keyfile; } ;
typedef  TYPE_1__ YuiPage ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__* YUI_PAGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_page_get_type () ; 

GtkWidget * yui_page_new(GKeyFile * keyfile) {
	GtkWidget * widget;
	YuiPage * yp;

	widget = GTK_WIDGET(g_object_new(yui_page_get_type(), NULL));
	yp = YUI_PAGE(widget);

	yp->keyfile = keyfile;

	return widget;
}