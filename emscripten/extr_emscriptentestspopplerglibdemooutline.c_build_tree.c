#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_14__ {int /*<<< orphan*/  value_name; } ;
struct TYPE_12__ {TYPE_2__* dest; } ;
struct TYPE_10__ {int /*<<< orphan*/  title; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_3__ goto_dest; TYPE_1__ any; } ;
struct TYPE_11__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  PopplerIndexIter ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  TYPE_4__ PopplerAction ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GWeakNotify ;
typedef  TYPE_5__ GEnumValue ;
typedef  int /*<<< orphan*/  GEnumClass ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OUTLINE_ACTION_COLUMN ; 
 int /*<<< orphan*/  OUTLINE_ACTION_TYPE_COLUMN ; 
 int /*<<< orphan*/  OUTLINE_EXPAND_COLUMN ; 
 int /*<<< orphan*/  OUTLINE_TITLE_COLUMN ; 
 scalar_t__ POPPLER_ACTION_GOTO_DEST ; 
 scalar_t__ POPPLER_DEST_NAMED ; 
 int /*<<< orphan*/  POPPLER_TYPE_ACTION_TYPE ; 
 TYPE_5__* g_enum_get_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_escape_text (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_object_weak_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ g_type_class_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 scalar_t__ poppler_action_free ; 
 int /*<<< orphan*/  poppler_index_iter_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* poppler_index_iter_get_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_index_iter_get_child (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_index_iter_is_open (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_index_iter_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_tree (PopplerDocument  *document,
	    GtkTreeModel     *model,
	    GtkTreeIter      *parent,
	    PopplerIndexIter *iter)
{

	do {
		GtkTreeIter       tree_iter;
		PopplerIndexIter *child;
		PopplerAction    *action;
		gboolean          expand;
		gchar            *markup;
		GEnumValue       *enum_value;

		action = poppler_index_iter_get_action (iter);
		expand = poppler_index_iter_is_open (iter);

		if (!action)
			continue;

		markup = g_markup_escape_text (action->any.title, -1);
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_ACTION_TYPE), action->type);
		
		if (action->type == POPPLER_ACTION_GOTO_DEST &&
		    action->goto_dest.dest->type == POPPLER_DEST_NAMED) {
			/* TODO */
		}			

		gtk_tree_store_append (GTK_TREE_STORE (model), &tree_iter, parent);
		gtk_tree_store_set (GTK_TREE_STORE (model), &tree_iter,
				    OUTLINE_TITLE_COLUMN, markup,
				    OUTLINE_ACTION_TYPE_COLUMN, enum_value->value_name,
				    OUTLINE_EXPAND_COLUMN, expand,
				    OUTLINE_ACTION_COLUMN, action,
				    -1);
		g_object_weak_ref (G_OBJECT (model),
				   (GWeakNotify)poppler_action_free,
				   action);

		g_free (markup);

		child = poppler_index_iter_get_child (iter);
		if (child)
			build_tree (document, model, &tree_iter, child);
		poppler_index_iter_free (child);
	} while (poppler_index_iter_next (iter));
}