#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_2__ hb_title_t ;
struct TYPE_8__ {int /*<<< orphan*/  lang; } ;
typedef  TYPE_3__ hb_subtitle_t ;
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
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*,int,double,int) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static void
subtitle_track_opts_set(signal_user_data_t *ud, const gchar *name,
                        void *opts, const void* data)
{
    (void)opts;   // Silence "unused variable" warning
    const hb_title_t *title = (const hb_title_t*)data;
    GtkTreeIter iter;
    GtkListStore *store;
    hb_subtitle_t * subtitle;
    gint ii, count = 0;

    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);

    if (title != NULL)
    {
        count = hb_list_count( title->list_subtitle );
    }
    for (ii = 0; ii < count; ii++)
    {
        gchar *opt;
        char idx[4];

        subtitle = hb_list_item(title->list_subtitle, ii);
        opt = g_strdup_printf("%d - %s", ii+1, subtitle->lang);
        snprintf(idx, 4, "%d", ii);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                    0, opt,
                    1, TRUE,
                    2, idx,
                    3, (gdouble)ii,
                    -1);
        g_free(opt);
    }
    if (count <= 0)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, _("None"),
                           1, TRUE,
                           2, "0",
                           3, 0.0,
                           -1);
    }
    gtk_combo_box_set_active (combo, 0);
}