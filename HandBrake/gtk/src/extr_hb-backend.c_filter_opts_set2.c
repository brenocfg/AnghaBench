#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_7__ {scalar_t__ index; int /*<<< orphan*/  short_name; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ hb_filter_param_t ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,double,int) ; 
 TYPE_2__* hb_filter_param_get_presets (int) ; 
 TYPE_2__* hb_filter_param_get_tunes (int) ; 

__attribute__((used)) static void
filter_opts_set2(signal_user_data_t *ud, const gchar *name,
                 int filter_id, int preset)
{
    GtkTreeIter iter;
    GtkListStore *store;
    gint ii;
    gchar *str;

    if (name == NULL) return;
    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);
    hb_filter_param_t * param;
    if (preset)
    {
        param = hb_filter_param_get_presets(filter_id);
    }
    else
    {
        param = hb_filter_param_get_tunes(filter_id);
    }
    for (ii = 0; param != NULL && param[ii].name != NULL; ii++)
    {
        gtk_list_store_append(store, &iter);
        str = g_strdup_printf("<small>%s</small>",
                              gettext(param[ii].name));
        gtk_list_store_set(store, &iter,
                           0, str,
                           1, TRUE,
                           2, param[ii].short_name,
                           3, (double)param[ii].index,
                           -1);
        g_free(str);
    }
}