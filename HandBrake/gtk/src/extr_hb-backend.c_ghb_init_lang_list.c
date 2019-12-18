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
typedef  int /*<<< orphan*/  signal_user_data_t ;
struct TYPE_5__ {scalar_t__* native_name; char* eng_name; int /*<<< orphan*/  iso639_2; } ;
typedef  TYPE_1__ iso639_lang_t ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_TREE_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_init_lang_list_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int) ; 
 int /*<<< orphan*/  gtk_tree_view_get_model (int /*<<< orphan*/ *) ; 
 TYPE_1__* lang_get_any () ; 
 TYPE_1__* lang_get_next (TYPE_1__ const*) ; 
 int lang_lookup_index (int /*<<< orphan*/ ) ; 

void ghb_init_lang_list(GtkTreeView *tv, signal_user_data_t *ud)
{
    GtkTreeIter    iter;
    GtkTreeStore * ts;

    ghb_init_lang_list_model(tv);
    ts = GTK_TREE_STORE(gtk_tree_view_get_model(tv));

    const iso639_lang_t *iso639;
    for (iso639 = lang_get_any(); iso639 != NULL;
         iso639 = lang_get_next(iso639))
    {
        int          index = lang_lookup_index(iso639->iso639_2);
        const char * lang;
        if (iso639->native_name != NULL && iso639->native_name[0] != 0)
        {
            lang = iso639->native_name;
        }
        else
        {
            lang = iso639->eng_name;
        }
        gtk_tree_store_append(ts, &iter, NULL);
        gtk_tree_store_set(ts, &iter, 0, lang, 1, index, -1);
    }
}