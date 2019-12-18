#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int index; } ;
typedef  TYPE_11__ hb_title_t ;
struct TYPE_20__ {int ttn; size_t cell_start; size_t cell_end; size_t cell_cur; int in_sync; scalar_t__ in_cell; scalar_t__ cell_overlap; scalar_t__ pack_len; scalar_t__ block; scalar_t__ next_vobu; TYPE_10__* pgc; TYPE_14__* ifo; scalar_t__ title_block_count; scalar_t__ title_end; scalar_t__ title_start; int /*<<< orphan*/  vts; int /*<<< orphan*/  reader; int /*<<< orphan*/  file; TYPE_3__* vmg; } ;
typedef  TYPE_12__ hb_dvdread_t ;
struct TYPE_21__ {TYPE_12__ dvdread; } ;
typedef  TYPE_13__ hb_dvd_t ;
struct TYPE_31__ {scalar_t__ first_sector; scalar_t__ last_sector; } ;
struct TYPE_30__ {TYPE_7__* pgci_srp; } ;
struct TYPE_29__ {TYPE_10__* pgc; } ;
struct TYPE_28__ {TYPE_5__* title; } ;
struct TYPE_27__ {TYPE_4__* ptt; } ;
struct TYPE_26__ {int pgcn; int pgn; } ;
struct TYPE_25__ {TYPE_2__* tt_srpt; } ;
struct TYPE_24__ {TYPE_1__* title; } ;
struct TYPE_23__ {int vts_ttn; int /*<<< orphan*/  title_set_nr; } ;
struct TYPE_22__ {TYPE_8__* vts_pgcit; TYPE_6__* vts_ptt_srpt; } ;
struct TYPE_18__ {size_t* program_map; size_t nr_of_cells; TYPE_9__* cell_playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVDOpenFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVD_READ_TITLE_VOBS ; 
 int /*<<< orphan*/  FindNextCell (TYPE_12__*) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 TYPE_14__* ifoOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hb_dvdread_start( hb_dvd_t * e, hb_title_t *title, int chapter )
{
    hb_dvdread_t *d = &(e->dvdread);
    int pgc_id, pgn;
    int i;
    int t = title->index;

    /* Open the IFO and the VOBs for this title */
    d->vts = d->vmg->tt_srpt->title[t-1].title_set_nr;
    d->ttn = d->vmg->tt_srpt->title[t-1].vts_ttn;
    if( !( d->ifo = ifoOpen( d->reader, d->vts ) ) )
    {
        hb_error( "dvd: ifoOpen failed for VTS %d", d->vts );
        return 0;
    }
    if( !( d->file = DVDOpenFile( d->reader, d->vts,
                                  DVD_READ_TITLE_VOBS ) ) )
    {
        hb_error( "dvd: DVDOpenFile failed for VTS %d", d->vts );
        return 0;
    }

    /* Get title first and last blocks */
    pgc_id         = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[0].pgcn;
    pgn            = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[0].pgn;
    d->pgc         = d->ifo->vts_pgcit->pgci_srp[pgc_id-1].pgc;
    d->cell_start  = d->pgc->program_map[pgn - 1] - 1;
    d->cell_end    = d->pgc->nr_of_cells - 1;
    d->title_start = d->pgc->cell_playback[d->cell_start].first_sector;
    d->title_end   = d->pgc->cell_playback[d->cell_end].last_sector;

    /* Block count */
    d->title_block_count = 0;
    for( i = d->cell_start; i <= d->cell_end; i++ )
    {
        d->title_block_count += d->pgc->cell_playback[i].last_sector + 1 -
            d->pgc->cell_playback[i].first_sector;
    }

    /* Get pgc for the current chapter */
    pgc_id = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[chapter-1].pgcn;
    pgn    = d->ifo->vts_ptt_srpt->title[d->ttn-1].ptt[chapter-1].pgn;
    d->pgc = d->ifo->vts_pgcit->pgci_srp[pgc_id-1].pgc;

    /* Get the two first cells */
    d->cell_cur = d->pgc->program_map[pgn-1] - 1;
    FindNextCell( d );

    d->block     = d->pgc->cell_playback[d->cell_cur].first_sector;
    d->next_vobu = d->block;
    d->pack_len  = 0;
    d->cell_overlap = 0;
    d->in_cell = 0;
    d->in_sync = 2;

    return 1;
}