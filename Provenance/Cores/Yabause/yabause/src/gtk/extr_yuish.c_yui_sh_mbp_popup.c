#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guint ;
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
struct TYPE_8__ {int /*<<< orphan*/ * mbp_menu_item; int /*<<< orphan*/  mbp_menu; int /*<<< orphan*/ * mbpList; } ;
typedef  TYPE_1__ YuiSh ;
struct TYPE_9__ {scalar_t__ type; int button; int /*<<< orphan*/  time; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkMenu ;
typedef  TYPE_3__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDK_BUTTON_PRESS ; 
 int /*<<< orphan*/  GTK_CHECK_MENU_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_MENU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TYPE_CHECK_MENU_ITEM ; 
 int /*<<< orphan*/  G_SIGNAL_MATCH_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handlers_block_matched (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_handlers_unblock_matched (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_check_menu_item_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_popup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char**,int) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_selection_count_selected_rows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_select_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_unselect_all (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_view_get_path_at_pos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 

gint yui_sh_mbp_popup(GtkWidget * widget, GdkEventButton * event, gpointer data)
{
  GtkMenu *menu;
  GdkEventButton *event_button;
  YuiSh * sh2 = data;
  GtkTreeView * view;
  GtkTreeSelection * selection;
  GtkTreeIter iter;
  GtkTreeModel * model;
  gchar * flags_s;
  char *endptr;
  int i;
  guint signal_id;

  g_return_val_if_fail (data != NULL, FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  view  = GTK_TREE_VIEW(sh2->mbpList);
  menu = GTK_MENU(sh2->mbp_menu);

  if (event->type == GDK_BUTTON_PRESS) {
      event_button = (GdkEventButton *) event;
      if (event_button->button == 3) {

           GtkTreePath *path;

	  selection = gtk_tree_view_get_selection(view);

           if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(view), event->x, event->y, &path, NULL, NULL, NULL)) {
               gtk_tree_selection_unselect_all(selection);
               gtk_tree_selection_select_path(selection, path);
               gtk_tree_path_free(path);
           } 

	  gtk_tree_selection_get_selected(selection, &model, &iter);

          if (gtk_tree_selection_count_selected_rows(selection) == 0) return FALSE;

	  gtk_tree_model_get(model, &iter, 1, &flags_s, -1);

          signal_id = g_signal_lookup("activate", GTK_TYPE_CHECK_MENU_ITEM);

          for(i = 0;i < 6;i++) g_signal_handlers_block_matched(sh2->mbp_menu_item[i], G_SIGNAL_MATCH_DATA, signal_id, 0, NULL, NULL, sh2);

          for(i = 0;i < 6;i++) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[i]), FALSE);

          endptr = flags_s;
          while ( *endptr ) {
              switch (*endptr) {
	
                  case 'b': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[0]), TRUE); break;
                  case 'w': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[1]), TRUE); break;
                  case 'l': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[2]), TRUE); break;
                  case 'B': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[3]), TRUE); break;
                  case 'W': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[4]), TRUE); break;
                  case 'L': gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(sh2->mbp_menu_item[5]), TRUE); break;
              }
              endptr++;
          }

          for(i = 0;i < 6;i++) g_signal_handlers_unblock_matched(sh2->mbp_menu_item[i], G_SIGNAL_MATCH_DATA, signal_id, 0, NULL, NULL, sh2);

	  gtk_menu_popup (menu, NULL, NULL, NULL, NULL, event_button->button, event_button->time);
      }
  }

  return FALSE;
}