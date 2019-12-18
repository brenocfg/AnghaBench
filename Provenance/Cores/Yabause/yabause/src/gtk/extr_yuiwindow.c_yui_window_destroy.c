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
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_file_set_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_set_value (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  g_key_file_to_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_main_quit () ; 
 int /*<<< orphan*/  gtk_window_get_position (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  inifile ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void yui_window_destroy(GtkWidget * window) {
	gint x, y;
	char buffer[512];

	gtk_window_get_position(GTK_WINDOW(window), &x, &y);

	sprintf(buffer, "%d", x);
	g_key_file_set_value(keyfile, "Gtk", "X", buffer);
	sprintf(buffer, "%d", y);
	g_key_file_set_value(keyfile, "Gtk", "Y", buffer);

	g_file_set_contents(inifile, g_key_file_to_data(keyfile, 0, 0), -1, 0);
	gtk_main_quit();
}