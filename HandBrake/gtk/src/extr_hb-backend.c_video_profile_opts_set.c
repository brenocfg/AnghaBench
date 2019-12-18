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
struct TYPE_3__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gdouble ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ ,char*) ; 
 int ghb_get_video_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const* const,int,int /*<<< orphan*/ ,int,char const* const,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ *,int) ; 
 char** hb_video_encoder_get_profiles (int) ; 

__attribute__((used)) static void
video_profile_opts_set(signal_user_data_t *ud, const gchar *name,
                       void *opts, const void* data)
{
    (void)opts; // Silence "unused variable" warning
    (void)data; // Silence "unused variable" warning
    GtkTreeIter iter;
    GtkListStore *store;
    gint ii, count = 0;

    // Check if encoder has been set yet.
    // If not, bail
    GhbValue *value = ghb_dict_get(ud->settings, "VideoEncoder");
    if (value == NULL) return;

    int encoder = ghb_get_video_encoder(ud->settings);
    const char * const *profiles;
    profiles = hb_video_encoder_get_profiles(encoder);

    while (profiles && profiles[count]) count++;
    GtkWidget *w = GHB_WIDGET(ud->builder, "VideoProfile");
    gtk_widget_set_visible(w, count > 0);
    w = GHB_WIDGET(ud->builder, "VideoProfileLabel");
    gtk_widget_set_visible(w, count > 0);
    if (count == 0) return;

    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
    gtk_list_store_clear(store);

    for (ii = 0; ii < count; ii++)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, profiles[ii],
                           1, TRUE,
                           2, profiles[ii],
                           3, (gdouble)ii,
                           -1);
    }
}