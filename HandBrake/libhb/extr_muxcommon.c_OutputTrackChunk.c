#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int frames; int /*<<< orphan*/  mux_data; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ hb_track_t ;
struct TYPE_16__ {scalar_t__ pts; TYPE_2__** track; } ;
typedef  TYPE_3__ hb_mux_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* mux ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ;} ;
typedef  TYPE_4__ hb_mux_object_t ;
struct TYPE_14__ {scalar_t__ start; } ;
struct TYPE_18__ {scalar_t__ size; TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;

/* Variables and functions */
 TYPE_5__* mf_peek (TYPE_2__*) ; 
 TYPE_5__* mf_pull (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void OutputTrackChunk( hb_mux_t *mux, int tk, hb_mux_object_t *m )
{
    hb_track_t *track = mux->track[tk];
    hb_buffer_t *buf;

    while ( ( buf = mf_peek( track ) ) != NULL && buf->s.start < mux->pts )
    {
        buf = mf_pull( mux, tk );
        track->frames += 1;
        track->bytes  += buf->size;
        m->mux( m, track->mux_data, buf );
    }
}