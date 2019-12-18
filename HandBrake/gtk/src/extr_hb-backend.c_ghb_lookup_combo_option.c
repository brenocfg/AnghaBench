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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_STRING ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_combo_value (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

char*
ghb_lookup_combo_option(const gchar *name, const GhbValue *gval)
{
    if (gval == NULL)
        return NULL;
    GhbValue *gresult = lookup_combo_value(name, gval, GHB_STRING);
    const char *tmp = ghb_value_get_string(gresult);
    char *result = NULL;
    if (tmp != NULL)
    {
        result = g_strdup(tmp);
    }
    ghb_value_free(&gresult);
    return result;
}