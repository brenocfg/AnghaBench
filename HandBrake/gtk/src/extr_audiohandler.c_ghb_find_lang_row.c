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
typedef  int gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int) ; 
 scalar_t__ gtk_tree_model_get_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

gboolean ghb_find_lang_row(GtkTreeModel *model, GtkTreeIter *iter, int lang_idx)
{
    if (gtk_tree_model_get_iter_first(model, iter))
    {
        do
        {
            gint          index;

            gtk_tree_model_get(model, iter, 1, &index, -1);
            if (index >= lang_idx)
            {
                return TRUE;
            }
        } while (gtk_tree_model_iter_next(model, iter));
    }
    return FALSE;
}