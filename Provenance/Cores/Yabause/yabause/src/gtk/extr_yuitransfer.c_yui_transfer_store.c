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
struct TYPE_4__ {int /*<<< orphan*/  to_entry; int /*<<< orphan*/  to_label; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ YuiTransfer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  YUI_TRANSFER_STORE ; 
 scalar_t__ gtk_toggle_button_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_transfer_check (TYPE_1__*) ; 

__attribute__((used)) static void yui_transfer_store(GtkWidget * entry, YuiTransfer * yt) {
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(entry))) {
		yt->mode = YUI_TRANSFER_STORE;
		gtk_widget_set_sensitive(GTK_WIDGET(yt->to_label), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(yt->to_entry), TRUE);
		yui_transfer_check(yt);
	}
}