#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pts; int /*<<< orphan*/  rdy; } ;
typedef  TYPE_2__ hb_mux_t ;
struct TYPE_8__ {scalar_t__ start; } ;
struct TYPE_10__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_bitvec_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mf_push (TYPE_2__*,int,TYPE_3__*) ; 

__attribute__((used)) static void MoveToInternalFifos( int tk, hb_mux_t *mux, hb_buffer_t * buf )
{
    // move all the buffers on the track's fifo to our internal
    // fifo so that (a) we don't deadlock in the reader and
    // (b) we can control how data from multiple tracks is
    // interleaved in the output file.
    mf_push( mux, tk, buf );
    if ( buf->s.start >= mux->pts )
    {
        // buffer is past our next interleave point so
        // note that this track is ready to be output.
        hb_bitvec_set(mux->rdy, tk);
    }
}