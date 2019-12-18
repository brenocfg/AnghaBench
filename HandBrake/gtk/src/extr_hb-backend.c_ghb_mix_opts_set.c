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
struct TYPE_4__ {scalar_t__ amixdown; int /*<<< orphan*/  short_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ hb_mixdown_t ;
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* hb_mixdown_get_next (TYPE_1__ const*) ; 

void
ghb_mix_opts_set(GtkComboBox *combo)
{
    GtkTreeIter iter;
    GtkListStore *store;
    gchar *str;

    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);

    const hb_mixdown_t *mix;
    for (mix = hb_mixdown_get_next(NULL); mix != NULL;
         mix = hb_mixdown_get_next(mix))
    {
        gtk_list_store_append(store, &iter);
        str = g_strdup_printf("<small>%s</small>", mix->name);
        gtk_list_store_set(store, &iter,
                           0, str,
                           1, TRUE,
                           2, mix->short_name,
                           3, (gdouble)mix->amixdown,
                           -1);
        g_free(str);
    }
}