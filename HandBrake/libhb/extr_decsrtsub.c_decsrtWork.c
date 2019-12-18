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
struct TYPE_7__ {scalar_t__ start_time; scalar_t__ stop_time; int /*<<< orphan*/  line; TYPE_1__* job; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_8__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_6__ {scalar_t__ reader_pts_offset; scalar_t__ pts_to_stop; scalar_t__ pts_to_start; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/ * hb_buffer_eof_init () ; 
 int /*<<< orphan*/  hb_srt_to_ssa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * srt_read (TYPE_2__*) ; 

__attribute__((used)) static int decsrtWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                       hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * out = NULL;

    if (pv->job->reader_pts_offset == AV_NOPTS_VALUE)
    {
        // We need to wait for reader to initialize it's pts offset so that
        // we know where to start reading SRTs.
        *buf_out = NULL;
        return HB_WORK_OK;
    }
    if (pv->start_time == AV_NOPTS_VALUE)
    {
        pv->start_time = pv->job->reader_pts_offset;
        if (pv->job->pts_to_stop > 0)
        {
            pv->stop_time = pv->job->pts_to_start + pv->job->pts_to_stop;
        }
    }
    out = srt_read( pv );
    if (out != NULL)
    {
        hb_srt_to_ssa(out, ++pv->line);
        *buf_out = out;
        return HB_WORK_OK;
    } else {
        *buf_out = hb_buffer_eof_init();
        return HB_WORK_DONE;
    }
}