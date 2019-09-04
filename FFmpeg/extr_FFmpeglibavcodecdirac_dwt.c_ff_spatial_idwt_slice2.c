#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int support; int decomposition_count; int width; int height; int stride; int /*<<< orphan*/  (* spatial_compose ) (TYPE_2__*,int,int,int,int) ;TYPE_1__* cs; } ;
struct TYPE_5__ {scalar_t__ y; } ;
typedef  TYPE_2__ DWTContext ;

/* Variables and functions */
 scalar_t__ FFMIN (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int,int) ; 

void ff_spatial_idwt_slice2(DWTContext *d, int y)
{
    int level, support = d->support;

    for (level = d->decomposition_count-1; level >= 0; level--) {
        int wl = d->width  >> level;
        int hl = d->height >> level;
        int stride_l = d->stride << level;

        while (d->cs[level].y <= FFMIN((y>>level)+support, hl))
            d->spatial_compose(d, level, wl, hl, stride_l);
    }
}