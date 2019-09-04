#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ ** pids; } ;
struct TYPE_12__ {TYPE_4__* opaque; } ;
struct TYPE_11__ {TYPE_4__* section_buf; } ;
struct TYPE_13__ {TYPE_2__ pes_filter; TYPE_1__ section_filter; } ;
struct TYPE_15__ {int pid; scalar_t__ type; TYPE_3__ u; } ;
struct TYPE_14__ {scalar_t__ merged_st; int /*<<< orphan*/  st; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_4__ PESContext ;
typedef  TYPE_5__ MpegTSFilter ;
typedef  TYPE_6__ MpegTSContext ;

/* Variables and functions */
 scalar_t__ MPEGTS_PES ; 
 scalar_t__ MPEGTS_SECTION ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_5__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 

__attribute__((used)) static void mpegts_close_filter(MpegTSContext *ts, MpegTSFilter *filter)
{
    int pid;

    pid = filter->pid;
    if (filter->type == MPEGTS_SECTION)
        av_freep(&filter->u.section_filter.section_buf);
    else if (filter->type == MPEGTS_PES) {
        PESContext *pes = filter->u.pes_filter.opaque;
        av_buffer_unref(&pes->buffer);
        /* referenced private data will be freed later in
         * avformat_close_input (pes->st->priv_data == pes) */
        if (!pes->st || pes->merged_st) {
            av_freep(&filter->u.pes_filter.opaque);
        }
    }

    av_free(filter);
    ts->pids[pid] = NULL;
}