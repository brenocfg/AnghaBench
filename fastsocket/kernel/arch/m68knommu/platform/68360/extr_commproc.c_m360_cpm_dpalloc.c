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
typedef  scalar_t__ uint ;

/* Variables and functions */
 scalar_t__ CPM_DP_NOSPACE ; 
 scalar_t__ dp_alloc_base ; 
 scalar_t__ dp_alloc_top ; 

uint
m360_cpm_dpalloc(uint size)
{
        uint    retloc;

        if ((dp_alloc_base + size) >= dp_alloc_top)
                return(CPM_DP_NOSPACE);

        retloc = dp_alloc_base;
        dp_alloc_base += size;

        return(retloc);
}