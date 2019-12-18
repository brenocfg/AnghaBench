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
typedef  int /*<<< orphan*/ * gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PERMOUSE ; 
 int /*<<< orphan*/  PERPAD ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_list_nth_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * gtk_container_get_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_get_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  pertype_display_mouse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pertype_display_pad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static void pertype_changed(GtkWidget * widget, gpointer data) {
	GtkTreePath * path;
	gchar * strpath;
	int i;
	GtkWidget * box = data;
	GList * children;
	GtkWidget * child;

	children = gtk_container_get_children(GTK_CONTAINER(box));
	for(i = 1;i < 4;i++) {
		child = g_list_nth_data(children, i);
		if (child != NULL) gtk_widget_destroy(child);
	}

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(widget), &path, NULL);

	if (path) {
		int i;

		strpath = gtk_tree_path_to_string(path);
		sscanf(strpath, "%d", &i);

		switch(i) {
			case 0:
				g_key_file_set_integer(keyfile, "General", "PerType", PERPAD);
				pertype_display_pad(box);
				break;
			case 1:
				g_key_file_set_integer(keyfile, "General", "PerType", PERMOUSE);
				pertype_display_mouse(box);
				break;
		}

		g_free(strpath);
		gtk_tree_path_free(path);
	}
}