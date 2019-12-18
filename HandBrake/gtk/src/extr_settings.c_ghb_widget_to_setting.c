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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*,...) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_setting_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_widget_value (int /*<<< orphan*/ *) ; 

void
ghb_widget_to_setting(GhbValue *settings, GtkWidget *widget)
{
    const gchar *key = NULL;
    GhbValue *value;

    if (widget == NULL) return;
    g_debug("ghb_widget_to_setting");
    // Find corresponding setting
    key = ghb_get_setting_key(widget);
    if (key == NULL) return;
    value = ghb_widget_value(widget);
    if (value != NULL)
    {
        ghb_dict_set(settings, key, value);
    }
    else
    {
        g_debug("No value found for %s\n", key);
    }
}