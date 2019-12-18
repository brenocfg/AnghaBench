#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_2__ signal_user_data_t ;
struct TYPE_9__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_7__ {int /*<<< orphan*/  description; } ;
struct TYPE_10__ {TYPE_1__ lang; } ;
typedef  TYPE_4__ hb_audio_config_t ;
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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*,int,double,int) ; 
 TYPE_4__* hb_list_audio_config_item (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

void
audio_track_opts_set(signal_user_data_t *ud, const gchar *name,
                     void *opts, const void* data)
{
    (void)opts;   // Silence "unused variable" warning
    const hb_title_t *title = (const hb_title_t*)data;
    GtkTreeIter iter;
    GtkListStore *store;
    hb_audio_config_t * audio;
    gint ii;
    gint count = 0;
    gchar *opt;

    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);
    if (title != NULL)
    {
        count = hb_list_count( title->list_audio );
    }
    if( count <= 0 )
    {
        // No audio. set some default
        opt = g_strdup_printf("<small>%s</small>", _("No Audio"));

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, opt,
                           1, TRUE,
                           2, "none",
                           3, -1.0,
                           -1);
        g_free(opt);
        return;
    }
    for (ii = 0; ii < count; ii++)
    {
        char idx[4];
        audio = hb_list_audio_config_item(title->list_audio, ii);
        opt = g_strdup_printf("<small>%d - %s</small>",
                              ii + 1, audio->lang.description);
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
    gtk_combo_box_set_active (combo, 0);
}