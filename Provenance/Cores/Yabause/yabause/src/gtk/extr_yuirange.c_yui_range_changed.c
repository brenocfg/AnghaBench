#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  combo; TYPE_1__* items; int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; } ;
typedef  TYPE_2__ YuiRange ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (TYPE_2__*) ; 
 size_t YUI_RANGE_CHANGED_SIGNAL ; 
 int /*<<< orphan*/  g_key_file_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_range_signals ; 

__attribute__((used)) static void yui_range_changed(GtkWidget * entry, YuiRange * yfe) {
	g_key_file_set_value(yfe->keyfile, yfe->group, yfe->key,
			yfe->items[gtk_combo_box_get_active(GTK_COMBO_BOX(yfe->combo))].value);
	g_signal_emit(G_OBJECT(yfe), yui_range_signals[YUI_RANGE_CHANGED_SIGNAL], 0);
}