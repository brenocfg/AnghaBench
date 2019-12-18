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
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; } ;
typedef  TYPE_1__ YuiCheckButton ;
typedef  int /*<<< orphan*/  GtkToggleButton ;

/* Variables and functions */
 int /*<<< orphan*/  G_OBJECT (TYPE_1__*) ; 
 size_t YUI_CHECK_BUTTON_CHANGED_SIGNAL ; 
 int /*<<< orphan*/  g_key_file_set_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_get_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yui_check_button_signals ; 

__attribute__((used)) static void yui_check_button_toggled(GtkToggleButton * button, YuiCheckButton * ycb) {
	g_key_file_set_boolean(ycb->keyfile, ycb->group, ycb->key,
	                       gtk_toggle_button_get_active(button));
	g_signal_emit(G_OBJECT(ycb), yui_check_button_signals[YUI_CHECK_BUTTON_CHANGED_SIGNAL], 0);
}