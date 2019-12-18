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
typedef  int /*<<< orphan*/  YuiWindow ;
typedef  int /*<<< orphan*/  YuiTransfer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * YUI_TRANSFERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_transfer_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_transfer_get_type () ; 
 int /*<<< orphan*/  yui_window_start (int /*<<< orphan*/ *) ; 

GtkWidget * yui_transfer_new(YuiWindow * yw) {
	GtkWidget * entry;
	YuiTransfer * yfe;

	entry = GTK_WIDGET(g_object_new(yui_transfer_get_type(), NULL));
	yfe = YUI_TRANSFERT(entry);

	gtk_widget_show_all(entry);

	yui_transfer_check(yfe);

	yui_window_start(yw);

	return entry;
}