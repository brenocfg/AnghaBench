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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int cursor; } ;
typedef  TYPE_1__ YuiVdp2 ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreePath ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_get_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  yui_vdp2_update (TYPE_1__*) ; 

void yui_vdp2_view_cursor_changed(GtkWidget * view, YuiVdp2 * vdp2) {
	GtkTreePath * path;
	gchar * strpath;
	int i;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(view), &path, NULL);

	if (path) {
		strpath = gtk_tree_path_to_string(path);

		sscanf(strpath, "%i", &i);

		vdp2->cursor = i;

		yui_vdp2_update(vdp2);

		g_free(strpath);
		gtk_tree_path_free(path);
	}
}