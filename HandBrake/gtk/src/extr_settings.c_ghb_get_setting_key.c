#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUILDABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * gtk_buildable_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/  const*,char*,int) ; 

const gchar*
ghb_get_setting_key(GtkWidget *widget)
{
    const gchar *name;

    g_debug("get_setting_key ()\n");
    if (widget == NULL) return NULL;
    name = gtk_buildable_get_name(GTK_BUILDABLE(widget));

    if (name == NULL || !strncmp(name, "Gtk", 3))
    {
        name = gtk_widget_get_name(widget);
    }
    if (name == NULL)
    {
        // Bad widget pointer?  Should never happen.
        g_debug("Bad widget\n");
        return NULL;
    }
    return name;
}