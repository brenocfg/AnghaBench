#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rgb; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* colormap ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ *) ; 

uint32_t hb_rgb_lookup_by_name(const char *color)
{
    int ii = 0;

    while (colormap[ii].name != NULL)
    {
        if (!strcasecmp(color, colormap[ii].name))
            return colormap[ii].rgb;
        ii++;
    }
    return 0;
}