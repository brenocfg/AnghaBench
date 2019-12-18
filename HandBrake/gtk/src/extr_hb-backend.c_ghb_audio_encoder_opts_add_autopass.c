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
struct TYPE_3__ {scalar_t__ codec; int /*<<< orphan*/  short_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ hb_encoder_t ;
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkListStore ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HB_ACODEC_AUTO_PASS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* hb_audio_encoder_get_from_codec (int /*<<< orphan*/ ) ; 

void
ghb_audio_encoder_opts_add_autopass(GtkComboBox *combo)
{
    GtkTreeIter iter;
    GtkListStore *store;
    gchar *str;
    const hb_encoder_t *enc;

    enc = hb_audio_encoder_get_from_codec(HB_ACODEC_AUTO_PASS);
    if (enc != NULL)
    {
        store = GTK_LIST_STORE(gtk_combo_box_get_model (combo));
        gtk_list_store_append(store, &iter);
        str = g_strdup_printf("<small>%s</small>", enc->name);
        gtk_list_store_set(store, &iter,
                           0, str,
                           1, TRUE,
                           2, enc->short_name,
                           3, (gdouble)enc->codec,
                           -1);
        g_free(str);
    }
}