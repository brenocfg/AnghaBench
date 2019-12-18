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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GhbDictIter ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_dict_iter_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ghb_ui_settings_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** widget_priority_list ; 

void
ghb_settings_to_ui(signal_user_data_t *ud, GhbValue *dict)
{
    GhbDictIter  iter;
    const gchar *key;
    GhbValue    *gval;
    int          ii;
    GhbValue    *tmp = ghb_value_dup(dict);

    if (dict == NULL)
        return;

    for (ii = 0; widget_priority_list[ii] != NULL; ii++)
    {
        key = widget_priority_list[ii];
        gval = ghb_dict_get_value(tmp, key);
        if (gval != NULL)
            ghb_ui_settings_update(ud, dict, key, gval);
    }

    iter = ghb_dict_iter_init(tmp);
    // middle (void*) cast prevents gcc warning "defreferencing type-punned
    // pointer will break strict-aliasing rules"
    while (ghb_dict_iter_next(tmp, &iter, &key, &gval))
    {
        ghb_ui_settings_update(ud, dict, key, gval);
    }
    ghb_value_free(&tmp);
}