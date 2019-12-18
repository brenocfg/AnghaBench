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
 char** hb_filter_get_tunes_short_name (int) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 

__attribute__((used)) static void showFilterTunes(FILE* const out, int filter_id)
{
    char ** tunes = hb_filter_get_tunes_short_name(filter_id);
    int     ii, count = 0;

    // Count number of entries we want to display
    for (ii = 0; tunes[ii] != NULL; ii++)
    {
        /*
        if (!strcasecmp(tunes[ii], "custom") || // skip custom
            !strcasecmp(tunes[ii], "off")    || // skip off
            !strcasecmp(tunes[ii], "default"))  // skip default
            continue;
        */
        count++;
    }

    // If there are no entries, display nothing.
    if (count == 0)
    {
        return;
    }
    fprintf(out, "                           Tunes:\n");
    for (ii = 0; tunes[ii] != NULL; ii++)
    {
        /*
        if (!strcasecmp(tunes[ii], "custom") || // skip custom
            !strcasecmp(tunes[ii], "off")    || // skip off
            !strcasecmp(tunes[ii], "default"))  // skip default
            continue;
        */
        fprintf(out, "                               %s\n", tunes[ii]);
    }

    hb_str_vfree(tunes);
}