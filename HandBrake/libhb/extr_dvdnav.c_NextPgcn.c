#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int next_pgc_nr; } ;
typedef  TYPE_3__ pgc_t ;
struct TYPE_9__ {TYPE_2__* vts_pgcit; } ;
typedef  TYPE_4__ ifo_handle_t ;
struct TYPE_7__ {int nr_of_pgci_srp; TYPE_1__* pgci_srp; } ;
struct TYPE_6__ {TYPE_3__* pgc; } ;

/* Variables and functions */
 int MAX_PGCN ; 

__attribute__((used)) static int NextPgcn( ifo_handle_t *ifo, int pgcn, uint32_t pgcn_map[MAX_PGCN/32] )
{
    int next_pgcn;
    pgc_t *pgc;

    pgcn_map[pgcn >> 5] |= (1 << (pgcn & 31));

    pgc = ifo->vts_pgcit->pgci_srp[pgcn-1].pgc;
    next_pgcn = pgc->next_pgc_nr;
    if ( next_pgcn < 1 || next_pgcn >= MAX_PGCN || next_pgcn > ifo->vts_pgcit->nr_of_pgci_srp )
        return 0;

    return pgcn_map[next_pgcn >> 5] & (1 << (next_pgcn & 31))? 0 : next_pgcn;
}