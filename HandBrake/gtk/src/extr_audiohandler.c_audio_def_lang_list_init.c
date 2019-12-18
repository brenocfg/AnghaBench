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
struct TYPE_4__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_def_selected_lang_list_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/  ghb_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_find_lang_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ghb_lookup_lang (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audio_def_lang_list_init(signal_user_data_t *ud)
{
    GhbValue     * lang_list;
    GtkTreeView  * tv;
    GtkTreeModel * avail;
    GtkTreeStore * selected;
    int            ii, count;

    tv       = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_avail_lang"));
    avail    = gtk_tree_view_get_model(tv);
    tv       = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "audio_selected_lang"));
    selected = GTK_TREE_STORE(gtk_tree_view_get_model(tv));

    // Clear selected languages.
    audio_def_selected_lang_list_clear(ud);

    lang_list = ghb_dict_get_value(ud->settings, "AudioLanguageList");
    if (lang_list == NULL)
    {
        lang_list = ghb_array_new();
        ghb_dict_set(ud->settings, "AudioLanguageList", lang_list);
    }

    count = ghb_array_len(lang_list);
    for (ii = 0; ii < count; )
    {
        GhbValue    * lang_val = ghb_array_get(lang_list, ii);
        int           idx      = ghb_lookup_lang(lang_val);
        GtkTreeIter   iter;

        if (ghb_find_lang_row(avail, &iter, idx))
        {
            gchar       * lang;
            gint          index;
            GtkTreeIter   pos;

            gtk_tree_model_get(avail, &iter, 0, &lang, 1, &index, -1);
            gtk_tree_store_append(selected, &pos, NULL);
            gtk_tree_store_set(selected, &pos, 0, lang, 1, index, -1);
            g_free(lang);
            gtk_tree_store_remove(GTK_TREE_STORE(avail), &iter);
            ii++;
        }
        else
        {
            // Error in list.  Probably duplicate languages.  Remove
            // this item from the list.
            ghb_array_remove(lang_list, ii);
            count--;
        }
    }
}