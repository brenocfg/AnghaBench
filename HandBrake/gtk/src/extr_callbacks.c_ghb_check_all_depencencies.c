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
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GhbDictIter ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 scalar_t__ dep_check (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_dict_iter_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * gtk_builder_get_object (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_can_focus (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rev_map ; 

void
ghb_check_all_depencencies(signal_user_data_t *ud)
{
    GhbDictIter iter;
    const gchar *dep_name;
    GhbValue *value;
    GObject *dep_object;

    g_debug("ghb_check_all_depencencies ()");
    if (rev_map == NULL) return;
    iter = ghb_dict_iter_init(rev_map);
    while (ghb_dict_iter_next(rev_map, &iter, &dep_name, &value))
    {
        gboolean sensitive;
        gboolean hide;

        dep_object = gtk_builder_get_object (ud->builder, dep_name);
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
            gtk_widget_hide(GTK_WIDGET(dep_object));
        }
        else
        {
            gtk_widget_show(GTK_WIDGET(dep_object));
        }
    }
}