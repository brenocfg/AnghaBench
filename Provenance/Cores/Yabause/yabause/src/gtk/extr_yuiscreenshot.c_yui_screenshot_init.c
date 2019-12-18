#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {struct TYPE_16__* image; } ;
typedef  TYPE_1__ YuiScreenshot ;
typedef  TYPE_1__ GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_STOCK_CLOSE ; 
 int /*<<< orphan*/  GTK_STOCK_REFRESH ; 
 int /*<<< orphan*/  GTK_STOCK_SAVE ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_button_new_from_stock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_hbutton_box_new () ; 
 TYPE_1__* gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_destroy ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yui_screenshot_update ; 
 TYPE_1__* yui_viewer_new () ; 
 int /*<<< orphan*/  yui_viewer_save ; 

__attribute__((used)) static void yui_screenshot_init (YuiScreenshot * yv) {
	GtkWidget * box;
	GtkWidget * button_box;
	GtkWidget * button;

	gtk_window_set_title(GTK_WINDOW(yv), "Screenshot");
	gtk_container_set_border_width(GTK_CONTAINER(yv), 4);

	box = gtk_vbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(yv), box);

	yv->image = yui_viewer_new();
	gtk_box_pack_start(GTK_BOX(box), yv->image, FALSE, FALSE, 0);
	gtk_widget_set_size_request(GTK_WIDGET(yv->image), 320, 224);

	button_box = gtk_hbutton_box_new();
	gtk_box_pack_start(GTK_BOX(box), button_box, FALSE, FALSE, 0);

	button = gtk_button_new_from_stock(GTK_STOCK_REFRESH);
	gtk_box_pack_start(GTK_BOX(button_box), button, FALSE, FALSE, 0);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(yui_screenshot_update), yv);

	button = gtk_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_box_pack_start(GTK_BOX(button_box), button, FALSE, FALSE, 0);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(yui_viewer_save), yv->image);

	button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
	gtk_box_pack_start(GTK_BOX(button_box), button, FALSE, FALSE, 0);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), yv);
}