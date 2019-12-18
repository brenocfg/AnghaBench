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
typedef  int /*<<< orphan*/  hb_preset_index_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ *) ; 
 int HB_PRESET_TYPE_CUSTOM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* g_strdup_printf (char*,char*,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_tooltip_text (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * hb_preset_get (int /*<<< orphan*/ *) ; 
 char* preset_get_fullname (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_preset_menu_button_label(signal_user_data_t *ud, hb_preset_index_t *path)
{
    char              * fullname, * text;
    const char        * description;
    GtkLabel          * label;
    GtkWidget         * widget;
    GhbValue          * dict;
    int                 type;

    dict = hb_preset_get(path);
    type = ghb_dict_get_int(dict, "Type");
    fullname = preset_get_fullname(path, " <span alpha=\"70%\">></span> ", TRUE);
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "presets_menu_button_label"));
    text = g_strdup_printf("%s%s", type == HB_PRESET_TYPE_CUSTOM ?
                                   "Custom" : "Official", fullname);
    gtk_label_set_markup(label, text);
    free(fullname);
    free(text);

    description = ghb_dict_get_string(dict, "PresetDescription");
    widget = GHB_WIDGET(ud->builder, "presets_menu_button");
    gtk_widget_set_tooltip_text(widget, description);
}