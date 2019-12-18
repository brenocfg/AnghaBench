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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_OK ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_MODAL ; 
 int /*<<< orphan*/  GTK_MESSAGE_WARNING ; 
#define  GTK_RESPONSE_CANCEL 129 
#define  GTK_RESPONSE_OK 128 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_KEY_FILE_NONE ; 
 int /*<<< orphan*/ * create_dialog1 () ; 
 int /*<<< orphan*/  g_file_set_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_load_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_to_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inifile ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_settings_load () ; 

void yui_conf(void) {
	gint result;
	GtkWidget * dialog;

	dialog = create_dialog1();

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	switch(result) {
		case GTK_RESPONSE_OK:
                {
			gboolean mustRestart;
			g_file_set_contents(inifile, g_key_file_to_data(keyfile, 0, 0), -1, 0);
			mustRestart = yui_settings_load();
			if (mustRestart) {
                       		GtkWidget* warningDlg = gtk_message_dialog_new (GTK_WINDOW(yui),
                                	                                        GTK_DIALOG_MODAL,
                                        	                                GTK_MESSAGE_WARNING,
                                                	                        GTK_BUTTONS_OK,
                                                        	                "You must restart Yabause before the changes take effect.");

                        	gtk_dialog_run (GTK_DIALOG(warningDlg));
                        	gtk_widget_destroy (warningDlg); 
			}
			break;
                }
		case GTK_RESPONSE_CANCEL:
			g_key_file_load_from_file(keyfile, inifile, G_KEY_FILE_NONE, 0);
			break;
	}
}