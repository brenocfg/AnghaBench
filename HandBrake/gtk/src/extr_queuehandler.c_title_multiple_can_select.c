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
typedef  int gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
title_multiple_can_select(GhbValue *settings_array, int index)
{
    gint count, ii;
    GhbValue *settings, *gdest;
    const char *dest;

    settings = ghb_array_get(settings_array, index);
    gdest = ghb_dict_get_value(settings, "destination");
    dest = ghb_value_get_string(gdest);
    if (dest == NULL)
        return FALSE;

    count = ghb_array_len(settings_array);
    count = count < index ? count : index;
    for (ii = 0; ii < count; ii++)
    {
        const char *tmp;

        settings = ghb_array_get(settings_array, ii);
        gdest = ghb_dict_get_value(settings, "destination");
        tmp = ghb_value_get_string(gdest);
        if (tmp != NULL && !strncmp(dest, tmp, PATH_MAX))
            return FALSE;
    }
    return TRUE;
}