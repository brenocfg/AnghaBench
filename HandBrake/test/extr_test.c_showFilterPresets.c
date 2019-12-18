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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ * const,char*,...) ; 
 char** hb_filter_get_presets_short_name (int) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static void showFilterPresets(FILE* const out, int filter_id)
{
    char ** names = hb_filter_get_presets_short_name(filter_id);
    int     ii, count = 0;

    // Count number of entries we want to display
    for (ii = 0; names[ii] != NULL; ii++)
    {
        if (!strcasecmp(names[ii], "custom") || // skip custom
            !strcasecmp(names[ii], "off")    || // skip off
            !strcasecmp(names[ii], "default"))  // skip default
            continue;
        count++;
    }

    // If there are no entries, display nothing.
    if (count == 0)
    {
        return;
    }
    fprintf(out, "                           Presets:\n");
    for (ii = 0; names[ii] != NULL; ii++)
    {
        if (!strcasecmp(names[ii], "custom") || // skip custom
            !strcasecmp(names[ii], "off")    || // skip off
            !strcasecmp(names[ii], "default"))  // skip default
            continue;
        fprintf(out, "                               %s\n", names[ii]);
    }

    hb_str_vfree(names);
}