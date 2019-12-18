#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/  store; } ;
typedef  TYPE_1__ YuiVdp2 ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkAction ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_ACTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_action_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_toggle_action_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void yui_vdp2_sync(GtkAction * action, YuiVdp2 * yv) {
	GtkTreeIter iter;
    const gchar * name;

    name = gtk_action_get_name(action) + 7;

    if (!strcmp("nbg0", name))
	    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(yv->store), &iter, "1");
    else if (!strcmp("nbg1", name))
	    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(yv->store), &iter, "2");
    else if (!strcmp("nbg2", name))
	    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(yv->store), &iter, "3");
    else if (!strcmp("nbg3", name))
	    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(yv->store), &iter, "4");
    else if (!strcmp("rbg0", name))
	    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(yv->store), &iter, "5");

	gtk_list_store_set(yv->store, &iter, 1, gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action)), -1);
}