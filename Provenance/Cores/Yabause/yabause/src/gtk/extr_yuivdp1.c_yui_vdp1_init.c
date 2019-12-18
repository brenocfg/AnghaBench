#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/ * texture; scalar_t__ cursor; int /*<<< orphan*/  image; int /*<<< orphan*/  buffer; int /*<<< orphan*/  store; struct TYPE_27__* toolbar; } ;
typedef  TYPE_1__ YuiVdp1 ;
typedef  TYPE_1__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_TYPE_PIXBUF ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_PANED (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TEXT_VIEW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_TOOLBAR (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_TOOLBAR_ICONS ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 TYPE_1__* G_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_pixbuf_new () ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_hpaned_new () ; 
 int /*<<< orphan*/  gtk_list_store_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_paned_pack1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_paned_pack2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_scrolled_window_add_with_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_view_get_buffer (int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_text_view_new () ; 
 int /*<<< orphan*/  gtk_text_view_set_cursor_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_view_set_editable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_toolbar_new () ; 
 int /*<<< orphan*/  gtk_toolbar_set_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new_with_attributes (char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_headers_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_vpaned_new () ; 
 int /*<<< orphan*/  gtk_window_set_default_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yui_vdp1_destroy ; 
 int /*<<< orphan*/  yui_vdp1_view_cursor_changed ; 
 int /*<<< orphan*/  yui_viewer_new () ; 

__attribute__((used)) static void yui_vdp1_init (YuiVdp1 * yv) {
	GtkWidget * hbox, * vbox, * vbox2, * view;

	gtk_window_set_title(GTK_WINDOW(yv), "VDP1");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 0);
	gtk_container_add(GTK_CONTAINER(yv), vbox);

	yv->toolbar = gtk_toolbar_new();

	gtk_toolbar_set_style(GTK_TOOLBAR(yv->toolbar), GTK_TOOLBAR_ICONS);

	gtk_box_pack_start(GTK_BOX(vbox), yv->toolbar, FALSE, FALSE, 0);

	hbox = gtk_hpaned_new();
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 4);

	yv->store = gtk_list_store_new(2, G_TYPE_STRING, GDK_TYPE_PIXBUF);
	view = gtk_tree_view_new_with_model(GTK_TREE_MODEL (yv->store));
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), FALSE);
	{
		GtkWidget * scroll;
		GtkCellRenderer *renderer;
		GtkCellRenderer *icon;
		GtkTreeViewColumn *column;

		scroll = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Command", renderer, "text", 0, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW (view), column);

		icon = gtk_cell_renderer_pixbuf_new();
		g_object_set(icon, "xalign", 0, NULL);
		column = gtk_tree_view_column_new_with_attributes("Icon", icon, "pixbuf", 1, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW (view), column);

		gtk_container_add(GTK_CONTAINER(scroll), view);
		gtk_paned_pack1(GTK_PANED(hbox), scroll, FALSE, TRUE);
	}
	g_signal_connect(view, "cursor-changed", G_CALLBACK(yui_vdp1_view_cursor_changed), yv);

	g_signal_connect(G_OBJECT(yv), "delete-event", GTK_SIGNAL_FUNC(yui_vdp1_destroy), NULL);

	vbox2 = gtk_vpaned_new();
	gtk_paned_pack2(GTK_PANED(hbox), vbox2, TRUE, TRUE);
	{
		GtkWidget * scroll = gtk_scrolled_window_new(NULL, NULL);
		GtkWidget * text = gtk_text_view_new();
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
		gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text), FALSE);
		yv->buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text));
		gtk_container_add(GTK_CONTAINER(scroll), text);
		gtk_paned_pack1(GTK_PANED(vbox2), scroll, FALSE, TRUE);
	}
	yv->image = yui_viewer_new();
	{
		GtkWidget * scroll = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), yv->image);
		gtk_paned_pack2(GTK_PANED(vbox2), scroll, TRUE, TRUE);
	}

	yv->cursor = 0;
	yv->texture = NULL;

	gtk_window_set_default_size(GTK_WINDOW(yv), 500, 450);

	gtk_paned_set_position(GTK_PANED(hbox), 250);

	gtk_paned_set_position(GTK_PANED(vbox2), 200);
}