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
struct TYPE_4__ {char const* name; int /*<<< orphan*/  short_name; } ;
typedef  TYPE_1__ hb_filter_param_t ;

/* Variables and functions */
 TYPE_1__* hb_filter_param_get_presets (int) ; 
 TYPE_1__* hb_filter_param_get_tunes (int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

const char*
ghb_lookup_filter_name(int filter_id, const char *short_name, int preset)
{
    hb_filter_param_t *map;
    int ii;

    if (short_name == NULL)
    {
        return NULL;
    }
    if (preset)
    {
        map = hb_filter_param_get_presets(filter_id);
    }
    else
    {
        map = hb_filter_param_get_tunes(filter_id);
    }
    if (map == NULL)
    {
        return NULL;
    }
    for (ii = 0; map[ii].name != NULL; ii++)
    {
        if (!strcasecmp(map[ii].short_name, short_name))
        {
            return map[ii].name;
        }
    }
    return NULL;
}