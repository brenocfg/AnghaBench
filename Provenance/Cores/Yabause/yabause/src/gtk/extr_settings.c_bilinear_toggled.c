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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyfile ; 

__attribute__((used)) static void bilinear_toggled(GtkWidget * widget, gpointer data) {
	g_key_file_set_integer(keyfile, "General", "Bilinear", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
}