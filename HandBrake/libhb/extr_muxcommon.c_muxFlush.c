#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ntracks; scalar_t__ interleave; int /*<<< orphan*/  pts; TYPE_1__** track; int /*<<< orphan*/  m; } ;
typedef  TYPE_3__ hb_mux_t ;
struct TYPE_7__ {scalar_t__ out; scalar_t__ in; } ;
struct TYPE_6__ {TYPE_2__ mf; } ;

/* Variables and functions */
 int /*<<< orphan*/  OutputTrackChunk (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void muxFlush(hb_mux_t * mux)
{
    int ii, done = 0;

    while (!done)
    {
        done = 1;
        for (ii = 0; ii < mux->ntracks; ii++)
        {
            OutputTrackChunk(mux, ii, mux->m);
            if (mux->track[ii]->mf.out != mux->track[ii]->mf.in)
            {
                // track buffer is not empty
                done = 0;
            }
        }
        mux->pts += mux->interleave;
    }
}