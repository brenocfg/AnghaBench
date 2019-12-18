#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; } ;
struct TYPE_21__ {int mode; int parity; int tff; int /*<<< orphan*/  out_list; TYPE_15__** ref; TYPE_3__ output; int /*<<< orphan*/  unfiltered; int /*<<< orphan*/  frames; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_20__ {scalar_t__ combed; int flags; long long stop; long long start; scalar_t__ new_chap; } ;
struct TYPE_18__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; } ;
struct TYPE_22__ {TYPE_4__ s; TYPE_2__ f; } ;
typedef  TYPE_6__ hb_buffer_t ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; } ;
struct TYPE_16__ {TYPE_4__ s; TYPE_1__ f; } ;

/* Variables and functions */
 scalar_t__ HB_COMB_NONE ; 
 int MODE_DECOMB_BOB ; 
 int MODE_DECOMB_SELECTIVE ; 
 int PIC_FLAG_TOP_FIELD_FIRST ; 
 TYPE_6__* hb_buffer_dup (TYPE_15__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_6__* hb_buffer_list_head (int /*<<< orphan*/ *) ; 
 TYPE_6__* hb_buffer_list_tail (int /*<<< orphan*/ *) ; 
 TYPE_6__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yadif_filter (TYPE_5__*,TYPE_6__*,int,int) ; 

__attribute__((used)) static void process_frame( hb_filter_private_t * pv )
{
    if ((pv->mode & MODE_DECOMB_SELECTIVE) &&
        pv->ref[1]->s.combed == HB_COMB_NONE)
    {
        // Input buffer is not combed.  Just make a dup of it.
        hb_buffer_t * buf = hb_buffer_dup(pv->ref[1]);
        hb_buffer_list_append(&pv->out_list, buf);
        pv->frames++;
        pv->unfiltered++;
    }
    else
    {
        /* Determine if top-field first layout */
        int tff;
        if (pv->parity < 0)
        {
            tff = !!(pv->ref[1]->s.flags & PIC_FLAG_TOP_FIELD_FIRST);
        }
        else
        {
            tff = (pv->parity & 1) ^ 1;
        }

        /* deinterlace both fields if bob */
        int frame, num_frames = 1;
        if (pv->mode & MODE_DECOMB_BOB)
        {
            num_frames = 2;
        }

        // Will need up to 2 buffers simultaneously

        /* Perform yadif filtering */
        for (frame = 0; frame < num_frames; frame++)
        {
            hb_buffer_t * buf;
            int parity = frame ^ tff ^ 1;

            // tff for eedi2
            pv->tff = !parity;

            buf = hb_frame_buffer_init(pv->ref[1]->f.fmt,
                                       pv->ref[1]->f.width,
                                       pv->ref[1]->f.height);
            buf->f.color_prim     = pv->output.color_prim;
            buf->f.color_transfer = pv->output.color_transfer;
            buf->f.color_matrix   = pv->output.color_matrix;
            buf->f.color_range    = pv->output.color_range ;
            yadif_filter(pv, buf, parity, tff);

            /* Copy buffered settings to output buffer settings */
            buf->s = pv->ref[1]->s;

            hb_buffer_list_append(&pv->out_list, buf);
        }

        /* if this frame was deinterlaced and bob mode is engaged, halve
           the duration of the saved timestamps. */
        if (pv->mode & MODE_DECOMB_BOB)
        {
            hb_buffer_t *first  = hb_buffer_list_head(&pv->out_list);
            hb_buffer_t *second = hb_buffer_list_tail(&pv->out_list);
            first->s.stop -= (first->s.stop - first->s.start) / 2LL;
            second->s.start = first->s.stop;
            second->s.new_chap = 0;
        }
    }
}