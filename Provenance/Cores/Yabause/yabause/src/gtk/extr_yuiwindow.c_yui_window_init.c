#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/ * area; int /*<<< orphan*/  clean_handler; int /*<<< orphan*/ * menu; int /*<<< orphan*/ * box; int /*<<< orphan*/  log; struct TYPE_12__* logpopup; int /*<<< orphan*/  action_group; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkAccelGroup ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 TYPE_1__* GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/ * G_OBJECT (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * create_menu (TYPE_1__*) ; 
 char* g_build_filename (char const* const,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 char** g_get_system_data_dirs () ; 
 int /*<<< orphan*/  g_list_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gdk_pixbuf_new_from_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_accel_group_new () ; 
 int /*<<< orphan*/  gtk_action_group_get_action (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_action_group_list_actions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_action_group_new (char*) ; 
 int /*<<< orphan*/  gtk_action_set_sensitive (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_add_with_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_view_new () ; 
 int /*<<< orphan*/ * gtk_vbox_new (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_add_accel_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_icon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * yui_gl_new () ; 
 int /*<<< orphan*/  yui_set_accel_group ; 
 int /*<<< orphan*/  yui_window_create_actions (TYPE_1__*) ; 
 int /*<<< orphan*/  yui_window_destroy ; 
 int /*<<< orphan*/  yui_window_keep_clean ; 
 int /*<<< orphan*/  yui_window_keypress ; 
 int /*<<< orphan*/  yui_window_keyrelease ; 
 int /*<<< orphan*/  yui_window_log_delete ; 

__attribute__((used)) static void yui_window_init (YuiWindow * yw) {
	GtkAccelGroup * accel_group = gtk_accel_group_new();
	GtkWidget * scroll;

	yw->action_group = gtk_action_group_new("yui");
	yui_window_create_actions(yw);
	gtk_action_set_sensitive(gtk_action_group_get_action(yw->action_group, "pause"), FALSE);
	gtk_action_set_sensitive(gtk_action_group_get_action(yw->action_group, "reset"), FALSE);
	{
		GList * list = gtk_action_group_list_actions(yw->action_group);
		g_list_foreach(list, yui_set_accel_group, accel_group);
	}
	gtk_window_add_accel_group(GTK_WINDOW(yw), accel_group);

	{
		const gchar * const * data_dir;
		gboolean pngfound = FALSE;
		gchar * pngfile;

		data_dir = g_get_system_data_dirs();
		while (!pngfound && (*data_dir != NULL)) {
			pngfile = g_build_filename(*data_dir, "pixmaps", "yabause.png", NULL);
			if (g_file_test(pngfile, G_FILE_TEST_EXISTS)) {
				gtk_window_set_icon(GTK_WINDOW(yw), gdk_pixbuf_new_from_file(pngfile, NULL));
				pngfound = TRUE;
			}
			data_dir++;
		}

		if (!pngfound) {
			gtk_window_set_icon(GTK_WINDOW(yw), gdk_pixbuf_new_from_file("yabause.png", NULL));
		}
	}

	gtk_window_set_title (GTK_WINDOW(yw), "Yabause");

	yw->box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(yw), yw->box);

	yw->menu = create_menu(yw);
	gtk_box_pack_start(GTK_BOX(yw->box), yw->menu, FALSE, FALSE, 0);

	yw->area = yui_gl_new();
	gtk_box_pack_start(GTK_BOX(yw->box), yw->area, TRUE, TRUE, 0);
	gtk_widget_set_size_request(GTK_WIDGET(yw->area), 320, 224);

	g_signal_connect(G_OBJECT(yw), "delete-event", G_CALLBACK(yui_window_destroy), NULL);
	g_signal_connect(G_OBJECT(yw), "key-press-event", G_CALLBACK(yui_window_keypress), yw);
	g_signal_connect(G_OBJECT(yw), "key-release-event", G_CALLBACK(yui_window_keyrelease), yw);

	yw->logpopup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title( GTK_WINDOW( yw->logpopup ), "Yabause Logs" );
	gtk_widget_set_size_request( yw->logpopup, 500, 300 );
	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(yw->logpopup), scroll);
	g_signal_connect(G_OBJECT(yw->logpopup), "delete-event", G_CALLBACK(yui_window_log_delete), yw);

	yw->log = gtk_text_view_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), yw->log);

	gtk_widget_show(yw->box);
	gtk_widget_show_all(yw->menu);
	gtk_widget_show(yw->area);

	yw->clean_handler = g_signal_connect(yw->area, "expose-event", G_CALLBACK(yui_window_keep_clean), yw);
	yw->state = 0;
}