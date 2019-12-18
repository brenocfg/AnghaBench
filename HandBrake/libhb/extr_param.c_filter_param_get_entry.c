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
struct TYPE_4__ {int /*<<< orphan*/ * short_name; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ hb_filter_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_filter_param_t*
filter_param_get_entry(hb_filter_param_t *table, const char *name, int count)
{
    if (table == NULL || name == NULL)
        return NULL;

    int ii;
    for (ii = 0; ii < count; ii++)
    {
        if ((table[ii].name != NULL && !strcasecmp(name, table[ii].name)) ||
            (table[ii].short_name != NULL &&
             !strcasecmp(name, table[ii].short_name)))
        {
            return &table[ii];
        }
    }
    return NULL;
}