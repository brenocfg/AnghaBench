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
struct TYPE_4__ {scalar_t__ index; int /*<<< orphan*/ * name; int /*<<< orphan*/ * short_name; } ;
typedef  TYPE_1__ hb_filter_param_t ;
typedef  scalar_t__ gint64 ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 scalar_t__ GHB_BOOL ; 
 scalar_t__ GHB_DOUBLE ; 
 scalar_t__ GHB_INT ; 
 scalar_t__ GHB_STRING ; 
 scalar_t__ ghb_value_get_int (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_value_get_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

const hb_filter_param_t*
find_param_entry(const hb_filter_param_t *param, const GhbValue *gval)
{
    gint ii;

    if (param == NULL)
        return NULL;

    if (ghb_value_type(gval) == GHB_STRING)
    {
        const gchar *str;
        str = ghb_value_get_string(gval);
        for (ii = 0; param[ii].name != NULL; ii++)
        {
            if (strcmp(param[ii].short_name, str) == 0 ||
                strcmp(param[ii].name, str) == 0)
            {
                return &param[ii];
            }
        }
    }
    else if (ghb_value_type(gval) == GHB_INT ||
             ghb_value_type(gval) == GHB_DOUBLE ||
             ghb_value_type(gval) == GHB_BOOL)
    {
        gint64 val;
        val = ghb_value_get_int(gval);
        for (ii = 0; param[ii].name != NULL; ii++)
        {
            if ((gint64)param[ii].index == val)
            {
                return &param[ii];
            }
        }
    }
    return NULL;
}