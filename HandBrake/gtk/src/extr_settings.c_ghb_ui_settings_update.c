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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_OBJECT (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_update_widget (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_widget_to_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ghb_ui_settings_update(
    signal_user_data_t *ud,
    GhbValue *settings,
    const gchar *name,
    const GhbValue *value)
{
    GObject *object;

    g_debug("ghb_ui_update() %s", name);
    if (name == NULL || value == NULL)
        return 0;
    object = GHB_OBJECT(ud->builder, name);
    if (object == NULL)
    {
        g_debug("Failed to find widget for key: %s\n", name);
        return -1;
    }
    ghb_update_widget((GtkWidget*)object, value);
    // Its possible the value hasn't changed. Since settings are only
    // updated when the value changes, I'm initializing settings here as well.
    ghb_widget_to_setting(settings, (GtkWidget*)object);
    return 0;
}