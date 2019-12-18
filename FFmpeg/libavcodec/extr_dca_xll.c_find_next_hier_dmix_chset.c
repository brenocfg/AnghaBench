#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hier_chset; } ;
struct TYPE_7__ {size_t nchsets; TYPE_2__* chset; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAXllChSet ;

/* Variables and functions */
 scalar_t__ is_hier_dmix_chset (TYPE_2__*) ; 

__attribute__((used)) static DCAXllChSet *find_next_hier_dmix_chset(DCAXllDecoder *s, DCAXllChSet *c)
{
    if (c->hier_chset)
        while (++c < &s->chset[s->nchsets])
            if (is_hier_dmix_chset(c))
                return c;

    return NULL;
}