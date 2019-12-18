#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int amixdown; } ;
typedef  TYPE_1__ hb_mixdown_t ;

/* Variables and functions */
 int hb_mixdown_get_from_name (char const*) ; 
 TYPE_1__* hb_mixdown_get_next (TYPE_1__ const*) ; 

const hb_mixdown_t*
ghb_lookup_mixdown(const char *name)
{
    // First find an enabled mixdown
    int mix = hb_mixdown_get_from_name(name);

    // Now find the matching mixdown info
    const hb_mixdown_t *mixdown, *first;
    for (first = mixdown = hb_mixdown_get_next(NULL); mixdown != NULL;
         mixdown = hb_mixdown_get_next(mixdown))
    {
        if (mix == mixdown->amixdown)
        {
            return mixdown;
        }
    }
    // Return a default mixdown if nothing matches
    return first;
}