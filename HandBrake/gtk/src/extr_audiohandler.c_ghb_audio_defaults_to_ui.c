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
struct TYPE_5__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_def_lang_list_init (TYPE_1__*) ; 
 int /*<<< orphan*/  audio_def_settings_show (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_def_update_widgets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/  ghb_container_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_create_audio_settings_row (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_box_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ghb_audio_defaults_to_ui(signal_user_data_t *ud)
{
    GtkListBox *list_box;
    GhbValue *alist;
    int count, ii;

    audio_def_lang_list_init(ud);

    // Init the AudioList settings if necessary
    alist = ghb_dict_get_value(ud->settings, "AudioList");
    if (alist == NULL)
    {
        alist = ghb_array_new();
        ghb_dict_set(ud->settings, "AudioList", alist);
    }

    // Empty the current list
    list_box = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "audio_list_default"));
    ghb_container_empty(GTK_CONTAINER(list_box));

    GtkWidget *widget;
    // Populate with new values
    count = ghb_array_len(alist);
    for (ii = 0; ii < count; ii++)
    {
        GhbValue *adict;

        adict = ghb_array_get(alist, ii);
        widget = ghb_create_audio_settings_row(ud);
        gtk_list_box_insert(list_box, widget, -1);
        audio_def_update_widgets(widget, adict);
    }
    // Add row with "Add" button
    widget = ghb_create_audio_settings_row(ud);
    audio_def_settings_show(widget, FALSE);
    gtk_list_box_insert(list_box, widget, -1);
}