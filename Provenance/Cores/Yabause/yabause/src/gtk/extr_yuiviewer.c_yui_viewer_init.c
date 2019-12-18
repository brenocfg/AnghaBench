#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * pixbuf; } ;
typedef  TYPE_1__ YuiViewer ;
typedef  TYPE_1__ GtkWidget ;

/* Variables and functions */
 int GDK_BUTTON_PRESS_MASK ; 
 int GDK_BUTTON_RELEASE_MASK ; 
 int /*<<< orphan*/  GTK_MENU_SHELL (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_STOCK_SAVE ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* gtk_image_menu_item_new_from_stock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* gtk_menu_new () ; 
 int /*<<< orphan*/  gtk_menu_shell_append (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_set_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show_all (TYPE_1__*) ; 
 int /*<<< orphan*/  my_popup_handler ; 
 int /*<<< orphan*/  yui_viewer_expose ; 
 int /*<<< orphan*/  yui_viewer_save ; 

__attribute__((used)) static void yui_viewer_init (YuiViewer * yv) {
	GtkWidget * menu;
	GtkWidget * item;

	gtk_widget_set_events(GTK_WIDGET(yv), GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

	menu = gtk_menu_new();
	item = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, NULL);

	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

	gtk_widget_show_all(menu);

	g_signal_connect_swapped(yv, "button-press-event", G_CALLBACK(my_popup_handler), menu);
	g_signal_connect(yv, "expose-event", G_CALLBACK(yui_viewer_expose), NULL);
	g_signal_connect_swapped(item, "activate", G_CALLBACK(yui_viewer_save), yv);

	yv->pixbuf = NULL;
}