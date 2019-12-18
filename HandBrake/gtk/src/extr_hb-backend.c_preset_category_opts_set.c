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
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  scalar_t__ gint ;
typedef  double gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char** calloc (scalar_t__,int) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 scalar_t__ ghb_strv_contains (char const**,char const*) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int,char const*,int,double,int) ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_presets_get () ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_get_bool (int /*<<< orphan*/ ) ; 
 char* hb_value_get_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
preset_category_opts_set(signal_user_data_t *ud, const gchar *name,
                         void *opts, const void* data)
{
    (void)opts; // Silence "unused variable" warning
    (void)data; // Silence "unused variable" warning
    GtkTreeIter     iter;
    GtkListStore  * store;
    gint            ii, jj, count;
    hb_value_t    * presets;
    GtkComboBox   * combo;
    char         ** categories;

    presets = hb_presets_get();
    count   = hb_value_array_len(presets);

    combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);

    categories = calloc(count + 1, sizeof(char*));
    for (ii = 0, jj = 0; ii < count; ii++)
    {
        const char * name;
        hb_value_t * folder = hb_value_array_get(presets, ii);

        if (!hb_value_get_bool(hb_dict_get(folder, "Folder")))
        {
            // Only list folders
            continue;
        }

        name = hb_value_get_string(hb_dict_get(folder, "PresetName"));
        if (name == NULL || name[0] == 0)
        {
            continue;
        }

        if (ghb_strv_contains((const char**)categories, name))
        {
            // Category is already in the list
            continue;
        }

        categories[jj++] = g_strdup(name);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, name,
                           1, TRUE,
                           2, name,
                           3, (gdouble)ii,
                           -1);
    }
    g_strfreev(categories);

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, "Add New Category",
                       1, TRUE,
                       2, "new",
                       3, -1.0,
                       -1);
}