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
typedef  TYPE_1__* gpointer ;
typedef  int gint ;
typedef  char gchar ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ YuiFileEntry ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkFileChooserAction ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_OPEN ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER ; 
#define  GTK_RESPONSE_ACCEPT 129 
#define  GTK_RESPONSE_CANCEL 128 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_OPEN ; 
 int YUI_FILE_ENTRY_DIRECTORY ; 
 int gtk_dialog_run (int /*<<< orphan*/ ) ; 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * gtk_file_chooser_dialog_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* gtk_file_chooser_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_file_chooser_set_filename (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void yui_file_entry_browse(GtkWidget * widget, gpointer user_data) {
        GtkWidget * file_selector;
        gint result;
        const gchar * filename;
	YuiFileEntry * yfe = user_data;
	GtkFileChooserAction action;

	if (yfe->flags & YUI_FILE_ENTRY_DIRECTORY) {
		action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
	} else {
		action = GTK_FILE_CHOOSER_ACTION_OPEN;
	}

        file_selector = gtk_file_chooser_dialog_new ("Please choose a file", NULL, action,
                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	filename = gtk_entry_get_text(GTK_ENTRY(yfe->entry));
	if (filename[0] != '\0')
        	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_selector), filename);

        gtk_widget_show(file_selector);

        result = gtk_dialog_run(GTK_DIALOG(file_selector));

        switch(result) {
                case GTK_RESPONSE_ACCEPT:
                        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selector));
                        gtk_entry_set_text(GTK_ENTRY(yfe->entry), filename);
                        break;
                case GTK_RESPONSE_CANCEL:
                        break;
        }

        gtk_widget_destroy(file_selector);
}