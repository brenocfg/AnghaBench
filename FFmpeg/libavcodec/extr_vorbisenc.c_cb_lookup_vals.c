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

/* Variables and functions */
 int ff_vorbis_nth_root (int,int) ; 

__attribute__((used)) static int cb_lookup_vals(int lookup, int dimensions, int entries)
{
    if (lookup == 1)
        return ff_vorbis_nth_root(entries, dimensions);
    else if (lookup == 2)
        return dimensions *entries;
    return 0;
}