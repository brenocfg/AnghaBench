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
struct menu {int dummy; } ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GdkPixbuf ;
typedef  int /*<<< orphan*/  GdkColor ;

/* Variables and functions */
 size_t COL_BTNACT ; 
 size_t COL_BTNINC ; 
 size_t COL_BTNRAD ; 
 size_t COL_BTNVIS ; 
 size_t COL_COLOR ; 
 size_t COL_EDIT ; 
 int /*<<< orphan*/  COL_MENU ; 
 size_t COL_MOD ; 
 size_t COL_NAME ; 
 size_t COL_NO ; 
 size_t COL_OPTION ; 
 size_t COL_PIXBUF ; 
 size_t COL_PIXVIS ; 
 size_t COL_VALUE ; 
 size_t COL_YES ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GPOINTER_TO_INT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_color_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_colormap_alloc_colors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_colormap_get_system () ; 
 int /*<<< orphan*/ * gdk_pixbuf_new_from_xpm_data (char const**) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void set_node(GtkTreeIter * node, struct menu *menu, gchar ** row)
{
	GdkColor color;
	gboolean success;
	GdkPixbuf *pix;

	pix = gdk_pixbuf_new_from_xpm_data((const char **)
					   row[COL_PIXBUF]);

	gdk_color_parse(row[COL_COLOR], &color);
	gdk_colormap_alloc_colors(gdk_colormap_get_system(), &color, 1,
				  FALSE, FALSE, &success);

	gtk_tree_store_set(tree, node,
			   COL_OPTION, row[COL_OPTION],
			   COL_NAME, row[COL_NAME],
			   COL_NO, row[COL_NO],
			   COL_MOD, row[COL_MOD],
			   COL_YES, row[COL_YES],
			   COL_VALUE, row[COL_VALUE],
			   COL_MENU, (gpointer) menu,
			   COL_COLOR, &color,
			   COL_EDIT, GPOINTER_TO_INT(row[COL_EDIT]),
			   COL_PIXBUF, pix,
			   COL_PIXVIS, GPOINTER_TO_INT(row[COL_PIXVIS]),
			   COL_BTNVIS, GPOINTER_TO_INT(row[COL_BTNVIS]),
			   COL_BTNACT, GPOINTER_TO_INT(row[COL_BTNACT]),
			   COL_BTNINC, GPOINTER_TO_INT(row[COL_BTNINC]),
			   COL_BTNRAD, GPOINTER_TO_INT(row[COL_BTNRAD]),
			   -1);

	g_object_unref(pix);
}