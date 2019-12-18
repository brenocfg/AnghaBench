#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int out; int in; int flen; TYPE_4__** fifo; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffered_size; TYPE_1__ mf; } ;
typedef  TYPE_2__ hb_track_t ;
struct TYPE_9__ {int /*<<< orphan*/  buffered_size; TYPE_2__** track; } ;
typedef  TYPE_3__ hb_mux_t ;
struct TYPE_10__ {scalar_t__ size; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */

__attribute__((used)) static hb_buffer_t *mf_pull( hb_mux_t * mux, int tk )
{
    hb_track_t *track =mux->track[tk];
    hb_buffer_t *b = NULL;
    if ( track->mf.out != track->mf.in )
    {
        // the fifo isn't empty
        b = track->mf.fifo[track->mf.out & (track->mf.flen - 1)];
        ++track->mf.out;

        track->buffered_size -= b->size;
        mux->buffered_size -= b->size;
    }
    return b;
}