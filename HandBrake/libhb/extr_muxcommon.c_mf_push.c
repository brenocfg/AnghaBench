#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int flen; int in; int out; TYPE_4__** fifo; } ;
struct TYPE_11__ {scalar_t__ buffered_size; TYPE_1__ mf; } ;
typedef  TYPE_2__ hb_track_t ;
struct TYPE_12__ {int /*<<< orphan*/  buffered_size; int /*<<< orphan*/  allRdy; int /*<<< orphan*/  rdy; TYPE_2__** track; } ;
typedef  TYPE_3__ hb_mux_t ;
struct TYPE_13__ {scalar_t__ size; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ MAX_BUFFERING ; 
 int /*<<< orphan*/  free (TYPE_4__**) ; 
 int /*<<< orphan*/  hb_bitvec_cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_reduce (TYPE_4__*,scalar_t__) ; 
 TYPE_4__** malloc (int) ; 

__attribute__((used)) static void mf_push( hb_mux_t * mux, int tk, hb_buffer_t *buf )
{
    hb_track_t * track = mux->track[tk];
    uint32_t mask = track->mf.flen - 1;
    uint32_t in = track->mf.in;

    hb_buffer_reduce( buf, buf->size );
    if ( track->buffered_size > MAX_BUFFERING )
    {
        hb_bitvec_cpy(mux->rdy, mux->allRdy);
    }
    if ( ( ( in + 1 ) & mask ) == ( track->mf.out & mask ) )
    {
        // fifo is full - expand it to double the current size.
        // This is a bit tricky because when we change the size
        // it changes the modulus (mask) used to convert the in
        // and out counters to fifo indices. Since existing items
        // will be referenced at a new location after the expand
        // we can't just realloc the fifo. If there were
        // hundreds of fifo entries it would be worth it to have code
        // for each of the four possible before/after configurations
        // but these fifos are small so we just allocate a new chunk
        // of memory then do element by element copies using the old &
        // new masks then free the old fifo's memory..
        track->mf.flen *= 2;
        uint32_t nmask = track->mf.flen - 1;
        hb_buffer_t **nfifo = malloc( track->mf.flen * sizeof(*nfifo) );
        int indx = track->mf.out;
        while ( indx != track->mf.in )
        {
            nfifo[indx & nmask] = track->mf.fifo[indx & mask];
            ++indx;
        }
        free( track->mf.fifo );
        track->mf.fifo = nfifo;
        mask = nmask;
    }
    track->mf.fifo[in & mask] = buf;
    track->mf.in = in + 1;
    track->buffered_size += buf->size;
    mux->buffered_size += buf->size;
}