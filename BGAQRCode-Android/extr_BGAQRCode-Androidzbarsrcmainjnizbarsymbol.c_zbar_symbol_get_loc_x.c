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
struct TYPE_5__ {unsigned int npts; TYPE_1__* pts; } ;
typedef  TYPE_2__ zbar_symbol_t ;
struct TYPE_4__ {int x; } ;

/* Variables and functions */

int zbar_symbol_get_loc_x (const zbar_symbol_t *sym,
                           unsigned idx)
{
    if(idx < sym->npts)
        return(sym->pts[idx].x);
    else
        return(-1);
}