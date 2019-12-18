#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_11__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_9__ {int flags; scalar_t__ stop; int /*<<< orphan*/  frametype; } ;
struct TYPE_12__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int /*<<< orphan*/  HB_FRAME_SUBTITLE ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  hb_srt_to_ssa (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decutf8Work(hb_work_object_t * w,
                       hb_buffer_t **buf_in, hb_buffer_t **buf_out)
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;
    hb_buffer_t *out = *buf_in;

    *buf_in = NULL;
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        return HB_WORK_DONE;
    }

    // Warn if the subtitle's duration has not been passed through by the
    // demuxer, which will prevent the subtitle from displaying at all
    if (out->s.stop == 0)
    {
        hb_log("decutf8sub: subtitle packet lacks duration");
    }

    hb_srt_to_ssa(out, ++pv->line);
    out->s.frametype = HB_FRAME_SUBTITLE;
    *buf_out = out;

    return HB_WORK_OK;
}