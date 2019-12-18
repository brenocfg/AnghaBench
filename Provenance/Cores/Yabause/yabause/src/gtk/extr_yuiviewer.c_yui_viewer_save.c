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
typedef  int gint ;
struct TYPE_3__ {int w; int /*<<< orphan*/  pixbuf; } ;
typedef  TYPE_1__ YuiViewer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SAVE ; 
#define  GTK_RESPONSE_ACCEPT 129 
#define  GTK_RESPONSE_CANCEL 128 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_SAVE ; 
 int /*<<< orphan*/  gdk_pixbuf_save (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_chooser_dialog_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* gtk_file_chooser_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

void yui_viewer_save(YuiViewer * yv) {
        GtkWidget * file_selector;
        gint result;
	char * filename;
	int rowstride;

        file_selector = gtk_file_chooser_dialog_new ("Please choose a file", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);

        gtk_widget_show(file_selector);

        result = gtk_dialog_run(GTK_DIALOG(file_selector));

        switch(result) {
                case GTK_RESPONSE_ACCEPT:
			rowstride = yv->w * 4;
			rowstride += (rowstride % 4)? (4 - (rowstride % 4)): 0;
			filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selector));

			gdk_pixbuf_save(yv->pixbuf, filename, "png", NULL, NULL);

                        break;
                case GTK_RESPONSE_CANCEL:
                        break;
        }

        gtk_widget_destroy(file_selector);
}