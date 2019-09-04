#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int npts; int pts_alloc; TYPE_3__* pts; } ;
typedef  TYPE_1__ zbar_symbol_t ;
typedef  int /*<<< orphan*/  point_t ;
struct TYPE_6__ {int x; int y; } ;

/* Variables and functions */
 TYPE_3__* realloc (TYPE_3__*,int) ; 

__attribute__((used)) static inline void sym_add_point (zbar_symbol_t *sym,
                                  int x,
                                  int y)
{
    int i = sym->npts;
    if(++sym->npts >= sym->pts_alloc)
        sym->pts = realloc(sym->pts, ++sym->pts_alloc * sizeof(point_t));
    sym->pts[i].x = x;
    sym->pts[i].y = y;
}