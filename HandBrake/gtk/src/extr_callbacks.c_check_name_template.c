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
struct TYPE_3__ {int /*<<< orphan*/  prefs; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static gboolean
check_name_template(signal_user_data_t *ud, const char *str)
{
    if (ghb_dict_get_bool(ud->prefs, "auto_name"))
    {
        const gchar *template;

        template = ghb_dict_get_string(ud->prefs, "auto_name_template");
        if (strstr(template, str) != NULL)
            return TRUE;
    }
    return FALSE;
}