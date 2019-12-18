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
struct TYPE_4__ {int cursor; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  texture; int /*<<< orphan*/  buffer; int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ YuiVdp1 ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreePath ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vdp1DebugCommand (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vdp1DebugTexture (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YUI_VIEWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strstrip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_get_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  yui_vdp1_draw (TYPE_1__*) ; 
 int /*<<< orphan*/  yui_viewer_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_vdp1_view_cursor_changed(GtkWidget * view, YuiVdp1 * vdp1) {
	GtkTreePath * path;
	gchar * strpath;
	int i;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(view), &path, NULL);

	if (path) {
		gchar nameTemp[1024];

		yui_viewer_clear(YUI_VIEWER(vdp1->image));

		strpath = gtk_tree_path_to_string(path);

		sscanf(strpath, "%i", &i);

		vdp1->cursor = i;

		Vdp1DebugCommand(i, nameTemp);
		gtk_text_buffer_set_text(vdp1->buffer, g_strstrip(nameTemp), -1);
		vdp1->texture = Vdp1DebugTexture(i, &vdp1->w, &vdp1->h);
		yui_vdp1_draw(vdp1);

		g_free(strpath);
		gtk_tree_path_free(path);
	}
}