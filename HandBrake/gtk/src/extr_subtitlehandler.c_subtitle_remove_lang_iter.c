#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  iso639_lang_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ghb_clear_presets_selection (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ghb_find_lang_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ghb_iso639_lookup_by_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_lookup_lang (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int,int*,int) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_select_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_scroll_to_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtitle_update_pref_lang (TYPE_1__*,int /*<<< orphan*/  const*) ; 

void
subtitle_remove_lang_iter(GtkTreeModel *tm, GtkTreeIter *iter,
                          signal_user_data_t *ud)
{
    GtkTreeView      * avail;
    GtkTreeStore     * avail_ts;
    GtkTreeIter        pos, sibling;
    char             * lang;
    int                index;
    GtkTreePath      * tp  = gtk_tree_model_get_path(tm, iter);
    int              * ind = gtk_tree_path_get_indices(tp);
    int                row = ind[0];
    GhbValue         * slang_list;
    GtkTreeSelection * tsel;

    gtk_tree_path_free(tp);
    avail    = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "subtitle_avail_lang"));
    avail_ts = GTK_TREE_STORE(gtk_tree_view_get_model(avail));
    tsel     = gtk_tree_view_get_selection(avail);

    // Add to UI available language list box
    gtk_tree_model_get(tm, iter, 0, &lang, 1, &index, -1);
    if (ghb_find_lang_row(GTK_TREE_MODEL(avail_ts), &sibling, index))
    {
        gtk_tree_store_insert_before(avail_ts, &pos, NULL, &sibling);
    }
    else
    {
        gtk_tree_store_append(avail_ts, &pos, NULL);
    }
    gtk_tree_store_set(avail_ts, &pos, 0, lang, 1, index, -1);
    g_free(lang);

    // Select the item added to the available list and make it
    // visible in the scrolled window
    tp = gtk_tree_model_get_path(GTK_TREE_MODEL(avail_ts), &pos);
    gtk_tree_selection_select_iter(tsel, &pos);
    gtk_tree_view_scroll_to_cell(avail, tp, NULL, FALSE, 0, 0);
    gtk_tree_path_free(tp);

    // Remove from UI selected language list box
    gtk_tree_store_remove(GTK_TREE_STORE(tm), iter);

    // Remove from preset language list
    slang_list = ghb_dict_get_value(ud->settings, "SubtitleLanguageList");
    ghb_array_remove(slang_list, row);
    ghb_clear_presets_selection(ud);

    if (row == 0)
    {
        if (ghb_array_len(slang_list) > 0)
        {
            const iso639_lang_t *lang;
            GhbValue *entry = ghb_array_get(slang_list, 0);
            lang = ghb_iso639_lookup_by_int(ghb_lookup_lang(entry));
            subtitle_update_pref_lang(ud, lang);
        }
        else
        {
            subtitle_update_pref_lang(ud, NULL);
        }
    }
}