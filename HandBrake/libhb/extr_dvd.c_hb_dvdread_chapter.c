#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int* program_map; int nr_of_cells; } ;
typedef  TYPE_7__ pgc_t ;
struct TYPE_18__ {int ttn; int cell_cur; int cell_overlap; TYPE_6__* ifo; } ;
typedef  TYPE_8__ hb_dvdread_t ;
struct TYPE_19__ {TYPE_8__ dvdread; } ;
typedef  TYPE_9__ hb_dvd_t ;
struct TYPE_16__ {TYPE_5__* vts_pgcit; TYPE_3__* vts_ptt_srpt; } ;
struct TYPE_15__ {TYPE_4__* pgci_srp; } ;
struct TYPE_14__ {TYPE_7__* pgc; } ;
struct TYPE_13__ {TYPE_2__* title; } ;
struct TYPE_12__ {int nr_of_ptts; TYPE_1__* ptt; } ;
struct TYPE_11__ {int pgcn; int pgn; } ;

/* Variables and functions */

__attribute__((used)) static int hb_dvdread_chapter( hb_dvd_t * e )
{
    hb_dvdread_t *d = &(e->dvdread);
    int     i;
    int     pgc_id, pgn;
    int     nr_of_ptts = d->ifo->vts_ptt_srpt->title[d->ttn-1].nr_of_ptts;
    pgc_t * pgc;

    for( i = nr_of_ptts - 1;
         i >= 0;
         i-- )
    {
        /* Get pgc for chapter (i+1) */
        pgc_id = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[i].pgcn;
        pgn    = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[i].pgn;
        pgc    = d->ifo->vts_pgcit->pgci_srp[pgc_id-1].pgc;

        if( d->cell_cur - d->cell_overlap >= pgc->program_map[pgn-1] - 1 &&
            d->cell_cur - d->cell_overlap <= pgc->nr_of_cells - 1 )
        {
            /* We are in this chapter */
            return i + 1;
        }
    }

    /* End of title */
    return -1;
}