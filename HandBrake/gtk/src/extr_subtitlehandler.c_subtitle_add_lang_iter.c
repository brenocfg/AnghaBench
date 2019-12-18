#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_9__ {int /*<<< orphan*/  iso639_2; } ;
typedef  TYPE_2__ iso639_lang_t ;
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
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_clear_presets_selection (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ghb_iso639_lookup_by_int (int) ; 
 int /*<<< orphan*/ * ghb_string_value_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int,int*,int) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_selection_select_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_scroll_to_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtitle_update_pref_lang (TYPE_1__*,TYPE_2__ const*) ; 

void
subtitle_add_lang_iter(GtkTreeModel *tm, GtkTreeIter *iter,
                       signal_user_data_t *ud)
{
    GtkTreeView         * selected;
    GtkTreeStore        * selected_ts;
    GtkTreeIter           pos;
    GtkTreePath         * tp;
    char                * lang;
    int                   index;
    const iso639_lang_t * iso_lang;
    GhbValue            * glang, * slang_list;
    GtkTreeSelection    * tsel;

    selected    = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "subtitle_selected_lang"));
    selected_ts = GTK_TREE_STORE(gtk_tree_view_get_model(selected));
    tsel        = gtk_tree_view_get_selection(selected);

    // Add to UI selected language list box
    gtk_tree_model_get(tm, iter, 0, &lang, 1, &index, -1);
    gtk_tree_store_append(selected_ts, &pos, NULL);
    gtk_tree_store_set(selected_ts, &pos, 0, lang, 1, index, -1);
    g_free(lang);

    // Select the item added to the selected list and make it
    // visible in the scrolled window
    tp = gtk_tree_model_get_path(GTK_TREE_MODEL(selected_ts), &pos);
    gtk_tree_selection_select_iter(tsel, &pos);
    gtk_tree_view_scroll_to_cell(selected, tp, NULL, FALSE, 0, 0);
    gtk_tree_path_free(tp);

    // Remove from UI available language list box
    gtk_tree_store_remove(GTK_TREE_STORE(tm), iter);

    // Add to preset language list
    iso_lang = ghb_iso639_lookup_by_int(index);
    glang = ghb_string_value_new(iso_lang->iso639_2);
    slang_list = ghb_dict_get_value(ud->settings, "SubtitleLanguageList");
    if (ghb_array_len(slang_list) == 0)
    {
        subtitle_update_pref_lang(ud, iso_lang);
    }
    ghb_array_append(slang_list, glang);
    ghb_clear_presets_selection(ud);
}