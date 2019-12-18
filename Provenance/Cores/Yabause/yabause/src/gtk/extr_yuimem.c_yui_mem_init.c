#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gint ;
struct TYPE_35__ {int wLine; scalar_t__ address; int /*<<< orphan*/  store; struct TYPE_35__* quickCombo; struct TYPE_35__* toolbar; } ;
typedef  TYPE_1__ YuiMem ;
struct TYPE_36__ {scalar_t__ name; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  TYPE_1__ GtkToolItem ;
typedef  TYPE_1__ GtkCellRenderer ;
typedef  int /*<<< orphan*/  GtkAccelGroup ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_Page_Down ; 
 int /*<<< orphan*/  GDK_Page_Up ; 
 int /*<<< orphan*/  GTK_BIN (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CELL_RENDERER_MODE_EDITABLE ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_ENTRY (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_STOCK_GO_DOWN ; 
 int /*<<< orphan*/  GTK_STOCK_GO_UP ; 
 int /*<<< orphan*/  GTK_TOOLBAR (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_TOOLBAR_ICONS ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 TYPE_1__* G_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_cclosure_new (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (TYPE_1__*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_accel_group_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_accel_group_new () ; 
 TYPE_1__* gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_cell_renderer_text_new () ; 
 TYPE_1__* gtk_combo_box_entry_new_text () ; 
 int /*<<< orphan*/  gtk_combo_box_insert_text (int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_entry_set_width_chars (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_list_store_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_separator_tool_item_new () ; 
 TYPE_1__* gtk_tool_button_new_from_stock (int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_tool_item_new () ; 
 int /*<<< orphan*/  gtk_tool_item_set_expand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toolbar_insert (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_1__* gtk_toolbar_new () ; 
 int /*<<< orphan*/  gtk_toolbar_set_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new_with_attributes (char*,TYPE_1__*,char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_add_accel_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_default_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* quickAddress ; 
 int /*<<< orphan*/  yui_mem_address_changed ; 
 int /*<<< orphan*/  yui_mem_combo_changed ; 
 int /*<<< orphan*/  yui_mem_content_changed ; 
 int /*<<< orphan*/  yui_mem_destroy ; 
 int /*<<< orphan*/  yui_mem_pagedown_clicked ; 
 int /*<<< orphan*/  yui_mem_pagedown_pressed ; 
 int /*<<< orphan*/  yui_mem_pageup_clicked ; 
 int /*<<< orphan*/  yui_mem_pageup_pressed ; 

__attribute__((used)) static void yui_mem_init (YuiMem * yv) {
	GtkWidget * view;
	GtkCellRenderer * renderer;
	GtkTreeViewColumn * column;
	GtkAccelGroup *accelGroup;
	GtkToolItem * comboItem, * upbutton, * downbutton;
	GtkWidget * testbox, * vbox;
	gint i;

	gtk_window_set_title(GTK_WINDOW(yv), "Memory dump");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(yv), vbox);

	yv->toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(yv->toolbar), GTK_TOOLBAR_ICONS);
	gtk_box_pack_start(GTK_BOX(vbox), yv->toolbar, FALSE, FALSE, 0);

	gtk_toolbar_insert(GTK_TOOLBAR(yv->toolbar), gtk_separator_tool_item_new(), 0);

	comboItem = gtk_tool_item_new();
	gtk_tool_item_set_expand(comboItem, FALSE);
	gtk_toolbar_insert(GTK_TOOLBAR(yv->toolbar), comboItem, 1);

	downbutton = gtk_tool_button_new_from_stock(GTK_STOCK_GO_DOWN);
	g_signal_connect(downbutton, "clicked", G_CALLBACK(yui_mem_pagedown_clicked), yv);
	gtk_toolbar_insert(GTK_TOOLBAR(yv->toolbar), downbutton, 2);

	upbutton = gtk_tool_button_new_from_stock(GTK_STOCK_GO_UP);
	g_signal_connect(upbutton, "clicked", G_CALLBACK(yui_mem_pageup_clicked), yv);
	gtk_toolbar_insert(GTK_TOOLBAR(yv->toolbar), upbutton, 3);

	yv->quickCombo = gtk_combo_box_entry_new_text();

	gtk_entry_set_width_chars(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(yv->quickCombo))), 8);

	for ( i = 0 ; quickAddress[i].name ; i++ )
	  gtk_combo_box_insert_text( GTK_COMBO_BOX( yv->quickCombo ), i, quickAddress[i].name );
	gtk_combo_box_set_active( GTK_COMBO_BOX(yv->quickCombo), 0 );
	g_signal_connect(yv->quickCombo, "changed", G_CALLBACK(yui_mem_combo_changed), yv );
	g_signal_connect(gtk_bin_get_child(GTK_BIN(yv->quickCombo)), "activate", G_CALLBACK(yui_mem_address_changed), yv );

	testbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(testbox), yv->quickCombo, TRUE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(comboItem), testbox);

	yv->store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	view = gtk_tree_view_new_with_model(GTK_TREE_MODEL (yv->store));

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Address", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (view), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Dump", renderer, "text", 1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (view), column);
	g_object_set(G_OBJECT(renderer), "editable", TRUE, "mode", GTK_CELL_RENDERER_MODE_EDITABLE, NULL );
	g_signal_connect(G_OBJECT(renderer), "edited", GTK_SIGNAL_FUNC(yui_mem_content_changed), yv );
	gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(yv), "delete-event", GTK_SIGNAL_FUNC(yui_mem_destroy), NULL);

	accelGroup = gtk_accel_group_new ();
	gtk_accel_group_connect( accelGroup, GDK_Page_Up, 0, 0, 
				 g_cclosure_new (G_CALLBACK(yui_mem_pageup_pressed), yv, NULL) );
	gtk_accel_group_connect( accelGroup, GDK_Page_Down, 0, 0, 
				 g_cclosure_new (G_CALLBACK(yui_mem_pagedown_pressed), yv, NULL) );
	gtk_window_add_accel_group( GTK_WINDOW( yv ), accelGroup );

	yv->address = 0;
	yv->wLine = 8;

	gtk_window_set_default_size(GTK_WINDOW(yv), 300, -1);
}