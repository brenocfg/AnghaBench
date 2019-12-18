#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int count; TYPE_3__* list; } ;
struct TYPE_14__ {int count; TYPE_1__* list; } ;
struct TYPE_17__ {scalar_t__ hb_stream_type; TYPE_4__ pes; TYPE_2__ ts; } ;
typedef  TYPE_5__ hb_stream_t ;
struct TYPE_15__ {int next; scalar_t__ stream_kind; int /*<<< orphan*/  stream_id_ext; int /*<<< orphan*/  stream_id; } ;
struct TYPE_13__ {int pes_list; int /*<<< orphan*/  is_pcr; } ;

/* Variables and functions */
 scalar_t__ A ; 
 scalar_t__ U ; 
 scalar_t__ audio_inactive (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_stream_delete_ps_entry (TYPE_5__*,int) ; 
 int /*<<< orphan*/  hb_stream_delete_ts_entry (TYPE_5__*,int) ; 
 int /*<<< orphan*/  hb_stream_seek (TYPE_5__*,int) ; 
 scalar_t__ hb_stream_try_delete_ts_entry (TYPE_5__*,int) ; 
 scalar_t__ program ; 
 scalar_t__ transport ; 
 scalar_t__ ts_stream_kind (TYPE_5__*,int) ; 

__attribute__((used)) static void prune_streams(hb_stream_t *d)
{
    if ( d->hb_stream_type == transport )
    {
        int ii, jj;
        for ( ii = 0; ii < d->ts.count; ii++)
        {
            // If probing didn't find audio or video, and the pid
            // is not the PCR, remove the track
            if ( ts_stream_kind ( d, ii ) == U &&
                 !d->ts.list[ii].is_pcr )
            {
                hb_stream_delete_ts_entry(d, ii);
                continue;
            }

            if ( ts_stream_kind ( d, ii ) == A )
            {
                for ( jj = d->ts.list[ii].pes_list; jj != -1;
                      jj = d->pes.list[jj].next )
                {
                    if ( audio_inactive( d, d->pes.list[jj].stream_id,
                                         d->pes.list[jj].stream_id_ext ) )
                    {
                        hb_stream_delete_ps_entry(d, jj);
                    }
                }
                if ( !d->ts.list[ii].is_pcr &&
                     hb_stream_try_delete_ts_entry(d, ii) )
                {
                    continue;
                }
            }
        }
        // reset to beginning of file and reset some stream
        // state information
        hb_stream_seek( d, 0. );
    }
    else if ( d->hb_stream_type == program )
    {
        int ii;
        for ( ii = 0; ii < d->pes.count; ii++)
        {
            // If probing didn't find audio or video, remove the track
            if ( d->pes.list[ii].stream_kind == U )
            {
                hb_stream_delete_ps_entry(d, ii);
            }

            if ( d->pes.list[ii].stream_kind == A &&
                 audio_inactive( d, d->pes.list[ii].stream_id,
                                 d->pes.list[ii].stream_id_ext ) )
            {
                // this PID isn't wanted (we don't have a codec for it
                // or scan didn't find audio parameters)
                hb_stream_delete_ps_entry(d, ii);
                continue;
            }
        }
        // reset to beginning of file and reset some stream
        // state information
        hb_stream_seek( d, 0. );
    }
}