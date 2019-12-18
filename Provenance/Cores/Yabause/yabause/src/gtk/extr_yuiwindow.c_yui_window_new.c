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
struct TYPE_3__ {void* reset_func; int /*<<< orphan*/  run_func; int /*<<< orphan*/  init_data; void* init_func; int /*<<< orphan*/ * actions; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  int /*<<< orphan*/  YuiAction ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GSourceFunc ;
typedef  void* GCallback ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__* YUI_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_window_get_type () ; 

GtkWidget * yui_window_new(YuiAction * act, GCallback ifunc, gpointer idata,
		GSourceFunc rfunc, GCallback resetfunc) {
	GtkWidget * widget;
	YuiWindow * yw;

	widget = GTK_WIDGET(g_object_new(yui_window_get_type(), NULL));
	yw = YUI_WINDOW(widget);

	yw->actions = act;
	yw->init_func = ifunc;
	yw->init_data = idata;
	yw->run_func = rfunc;
	yw->reset_func = resetfunc;

	return widget;
}