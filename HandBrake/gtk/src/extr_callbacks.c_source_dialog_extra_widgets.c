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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkComboBoxText ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX_TEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _ (char*) ; 
 TYPE_2__* dvd_device_list () ; 
 int /*<<< orphan*/  free_drive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_dvd_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_text_append_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
source_dialog_extra_widgets(
    signal_user_data_t *ud,
    GtkWidget *dialog)
{
    GtkComboBoxText *combo;
    GList *drives, *link;

    g_debug("source_dialog_extra_widgets ()");
    combo = GTK_COMBO_BOX_TEXT(GHB_WIDGET(ud->builder, "source_device"));
    gtk_list_store_clear(GTK_LIST_STORE(
                gtk_combo_box_get_model(GTK_COMBO_BOX(combo))));

    link = drives = dvd_device_list();
    gtk_combo_box_text_append_text (combo, _("Not Selected"));
    while (link != NULL)
    {
        gchar *name = get_dvd_device_name(link->data);
        gtk_combo_box_text_append_text(combo, name);
        g_free(name);
        free_drive(link->data);
        link = link->next;
    }
    g_list_free(drives);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
}