#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint64 ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_5__ {size_t count; TYPE_1__* map; } ;
typedef  TYPE_2__ combo_opts_t ;
struct TYPE_4__ {scalar_t__ ivalue; int /*<<< orphan*/  option; int /*<<< orphan*/  shortOpt; } ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 scalar_t__ GHB_BOOL ; 
 scalar_t__ GHB_DOUBLE ; 
 scalar_t__ GHB_INT ; 
 scalar_t__ GHB_STRING ; 
 scalar_t__ ghb_value_get_int (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_value_get_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

gint
find_opt_entry(const combo_opts_t *opts, const GhbValue *gval)
{
    gint ii;

    if (opts == NULL)
        return 0;

    if (ghb_value_type(gval) == GHB_STRING)
    {
        const gchar *str;
        str = ghb_value_get_string(gval);
        for (ii = 0; ii < opts->count; ii++)
        {
            if (strcmp(opts->map[ii].shortOpt, str) == 0 ||
                strcmp(opts->map[ii].option, str) == 0)
            {
                break;
            }
        }
        return ii;
    }
    else if (ghb_value_type(gval) == GHB_INT ||
             ghb_value_type(gval) == GHB_DOUBLE ||
             ghb_value_type(gval) == GHB_BOOL)
    {
        gint64 val;
        val = ghb_value_get_int(gval);
        for (ii = 0; ii < opts->count; ii++)
        {
            if ((gint64)opts->map[ii].ivalue == val)
            {
                break;
            }
        }
        return ii;
    }
    return opts->count;
}