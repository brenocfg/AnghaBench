#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  scalar_t__ GType ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_TYPE_COMBO_BOX ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 scalar_t__ G_OBJECT_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ dep_check (TYPE_1__*,char const*,scalar_t__*) ; 
 int /*<<< orphan*/ * dep_map ; 
 int /*<<< orphan*/  g_debug (char*,char const*) ; 
 int /*<<< orphan*/  g_message (char*,char const*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 char* ghb_get_setting_key (int /*<<< orphan*/ *) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_builder_get_object (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_widget_get_visible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_can_focus (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 

void
ghb_check_dependency(
    signal_user_data_t *ud,
    GtkWidget *widget,
    const char *alt_name)
{
    GObject *dep_object;
    const gchar *name;
    GhbValue *array, *data;
    gint count, ii;
    const gchar *dep_name;
    GType type;

    if (widget != NULL)
    {
        type = G_OBJECT_TYPE(widget);
        if (type == GTK_TYPE_COMBO_BOX)
            if (gtk_combo_box_get_active(GTK_COMBO_BOX(widget)) < 0) return;
        name = ghb_get_setting_key(widget);
    }
    else
        name = alt_name;

    g_debug("ghb_check_dependency() %s", name);

    if (dep_map == NULL) return;
    array = ghb_dict_get(dep_map, name);
    count = ghb_array_len(array);
    for (ii = 0; ii < count; ii++)
    {
        gboolean sensitive;
        gboolean hide;

        data = ghb_array_get(array, ii);
        dep_name = ghb_value_get_string(data);
        dep_object = gtk_builder_get_object(ud->builder, dep_name);
        if (dep_object == NULL)
        {
            g_message("Failed to find dependent widget %s", dep_name);
            continue;
        }
        sensitive = dep_check(ud, dep_name, &hide);
        gtk_widget_set_sensitive(GTK_WIDGET(dep_object), sensitive);
        gtk_widget_set_can_focus(GTK_WIDGET(dep_object), sensitive);
        if (!sensitive && hide)
        {
            if (gtk_widget_get_visible(GTK_WIDGET(dep_object)))
            {
                gtk_widget_hide(GTK_WIDGET(dep_object));
            }
        }
        else
        {
            if (!gtk_widget_get_visible(GTK_WIDGET(dep_object)))
            {
                gtk_widget_show(GTK_WIDGET(dep_object));
            }
        }
    }
}