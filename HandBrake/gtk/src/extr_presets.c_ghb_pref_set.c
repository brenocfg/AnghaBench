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
typedef  char gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 void* ghb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_value_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * prefsDict ; 
 int /*<<< orphan*/  prefs_modified ; 

void
ghb_pref_set(GhbValue *settings, const gchar *key)
{
    const GhbValue *value, *value2;

    value = ghb_dict_get_value(settings, key);
    if (value != NULL)
    {
        GhbValue *dict;
        dict = ghb_dict_get(prefsDict, "Preferences");
        if (dict == NULL) return;
        value2 = ghb_dict_get(dict, key);
        if (ghb_value_cmp(value, value2) != 0)
        {
            ghb_dict_set(dict, key, ghb_value_dup(value));
            prefs_modified = TRUE;
        }
    }
}