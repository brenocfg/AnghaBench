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
struct TYPE_3__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * audio_settings_get_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_updates ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_widget_to_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audio_def_setting_update(signal_user_data_t *ud, GtkWidget *widget)
{
    GtkListBoxRow *row = audio_settings_get_row(widget);
    gint index = gtk_list_box_row_get_index(row);

    GhbValue *alist = ghb_dict_get_value(ud->settings, "AudioList");
    int count = ghb_array_len(alist);
    if (!block_updates && index >= 0 && index < count)
    {
        GhbValue *adict = ghb_array_get(alist, index);
        ghb_widget_to_setting(adict, widget);
    }
}