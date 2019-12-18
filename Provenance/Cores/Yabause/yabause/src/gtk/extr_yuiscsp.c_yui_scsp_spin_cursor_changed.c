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
struct TYPE_4__ {int /*<<< orphan*/  cursor; } ;
typedef  TYPE_1__ YuiScsp ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_spin_button_get_value_as_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_scsp_fill (TYPE_1__*) ; 

__attribute__((used)) static void yui_scsp_spin_cursor_changed(GtkWidget * spin, YuiScsp * scsp) {
	scsp->cursor = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));
	yui_scsp_fill(scsp);
}