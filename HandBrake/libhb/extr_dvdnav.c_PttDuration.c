#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_18__ {int nr_of_programs; int* program_map; int nr_of_cells; TYPE_6__* cell_playback; int /*<<< orphan*/  playback_time; } ;
typedef  TYPE_7__ pgc_t ;
struct TYPE_19__ {TYPE_5__* vts_pgcit; TYPE_3__* vts_ptt_srpt; } ;
typedef  TYPE_8__ ifo_handle_t ;
struct TYPE_17__ {scalar_t__ first_sector; scalar_t__ last_sector; } ;
struct TYPE_16__ {int nr_of_pgci_srp; TYPE_4__* pgci_srp; } ;
struct TYPE_15__ {TYPE_7__* pgc; } ;
struct TYPE_14__ {TYPE_2__* title; } ;
struct TYPE_13__ {TYPE_1__* ptt; } ;
struct TYPE_12__ {int pgcn; int pgn; } ;

/* Variables and functions */
 int FindNextCell (TYPE_7__*,int) ; 
 int MAX_PGCN ; 
 int NextPgcn (TYPE_8__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PgcWalkInit (int /*<<< orphan*/ *) ; 
 long long dvdtime2msec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 

__attribute__((used)) static uint64_t
PttDuration(ifo_handle_t *ifo, int ttn, int pttn, int *blocks, int *last_pgcn)
{
    int            pgcn, pgn;
    pgc_t        * pgc;
    uint64_t       duration = 0;
    int            cell_start, cell_end;
    int            i;

    *blocks = 0;

    // Initialize map of visited pgc's to prevent loops
    uint32_t pgcn_map[MAX_PGCN/32];
    PgcWalkInit( pgcn_map );
    pgcn   = ifo->vts_ptt_srpt->title[ttn-1].ptt[pttn-1].pgcn;
    pgn   = ifo->vts_ptt_srpt->title[ttn-1].ptt[pttn-1].pgn;
    if ( pgcn < 1 || pgcn > ifo->vts_pgcit->nr_of_pgci_srp || pgcn >= MAX_PGCN)
    {
        hb_log( "invalid PGC ID %d, skipping", pgcn );
        return 0;
    }

    if( pgn <= 0 || pgn > 99 )
    {
        hb_log( "scan: pgn %d not valid, skipping", pgn );
        return 0;
    }

    do
    {
        pgc = ifo->vts_pgcit->pgci_srp[pgcn-1].pgc;
        if (!pgc)
        {
            *blocks = 0;
            duration = 0;
            hb_log( "scan: pgc not valid, skipping" );
            break;
        }

        if (pgc->cell_playback == NULL)
        {
            *blocks = 0;
            duration = 0;
            hb_log("invalid PGC cell_playback table, skipping");
            break;
        }

        if (pgn > pgc->nr_of_programs)
        {
            pgn = 1;
            continue;
        }

        duration += 90LL * dvdtime2msec( &pgc->playback_time );

        cell_start = pgc->program_map[pgn-1] - 1;
        cell_end = pgc->nr_of_cells - 1;
        for(i = cell_start; i <= cell_end; i = FindNextCell(pgc, i))
        {
            *blocks += pgc->cell_playback[i].last_sector + 1 -
                pgc->cell_playback[i].first_sector;
        }
        *last_pgcn = pgcn;
        pgn = 1;
    } while((pgcn = NextPgcn(ifo, pgcn, pgcn_map)) != 0);
    return duration;
}