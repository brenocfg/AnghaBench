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
typedef  scalar_t__ gint ;
typedef  scalar_t__ gdouble ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
find_combo_item_by_int(GtkTreeModel *store, gint value, GtkTreeIter *iter)
{
    gdouble ivalue;
    gboolean foundit = FALSE;

    if (gtk_tree_model_get_iter_first (store, iter))
    {
        do
        {
            gtk_tree_model_get(store, iter, 3, &ivalue, -1);
            if (value == (gint)ivalue)
            {
                foundit = TRUE;
                break;
            }
        } while (gtk_tree_model_iter_next (store, iter));
    }
    return foundit;
}