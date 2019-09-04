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
struct TYPE_14__ {TYPE_3__* sps; } ;
struct TYPE_11__ {scalar_t__ slice_type; } ;
struct TYPE_16__ {int threads_type; TYPE_5__* ref; TYPE_4__ ps; int /*<<< orphan*/  nal_unit_type; TYPE_2__* avctx; TYPE_1__ sh; } ;
struct TYPE_15__ {int /*<<< orphan*/  tf; } ;
struct TYPE_13__ {int width; int height; scalar_t__ sao_enabled; } ;
struct TYPE_12__ {scalar_t__ skip_loop_filter; } ;
typedef  TYPE_6__ HEVCContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 scalar_t__ AVDISCARD_BIDIR ; 
 scalar_t__ AVDISCARD_NONINTRA ; 
 scalar_t__ AVDISCARD_NONKEY ; 
 scalar_t__ AVDISCARD_NONREF ; 
 int FF_THREAD_FRAME ; 
 scalar_t__ HEVC_SLICE_B ; 
 scalar_t__ HEVC_SLICE_I ; 
 int /*<<< orphan*/  IS_IDR (TYPE_6__*) ; 
 int /*<<< orphan*/  deblocking_filter_CTB (TYPE_6__*,int,int) ; 
 scalar_t__ ff_hevc_nal_is_nonref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sao_filter_CTB (TYPE_6__*,int,int) ; 

void ff_hevc_hls_filter(HEVCContext *s, int x, int y, int ctb_size)
{
    int x_end = x >= s->ps.sps->width  - ctb_size;
    int skip = 0;
    if (s->avctx->skip_loop_filter >= AVDISCARD_ALL ||
        (s->avctx->skip_loop_filter >= AVDISCARD_NONKEY && !IS_IDR(s)) ||
        (s->avctx->skip_loop_filter >= AVDISCARD_NONINTRA &&
         s->sh.slice_type != HEVC_SLICE_I) ||
        (s->avctx->skip_loop_filter >= AVDISCARD_BIDIR &&
         s->sh.slice_type == HEVC_SLICE_B) ||
        (s->avctx->skip_loop_filter >= AVDISCARD_NONREF &&
        ff_hevc_nal_is_nonref(s->nal_unit_type)))
        skip = 1;

    if (!skip)
        deblocking_filter_CTB(s, x, y);
    if (s->ps.sps->sao_enabled && !skip) {
        int y_end = y >= s->ps.sps->height - ctb_size;
        if (y && x)
            sao_filter_CTB(s, x - ctb_size, y - ctb_size);
        if (x && y_end)
            sao_filter_CTB(s, x - ctb_size, y);
        if (y && x_end) {
            sao_filter_CTB(s, x, y - ctb_size);
            if (s->threads_type & FF_THREAD_FRAME )
                ff_thread_report_progress(&s->ref->tf, y, 0);
        }
        if (x_end && y_end) {
            sao_filter_CTB(s, x , y);
            if (s->threads_type & FF_THREAD_FRAME )
                ff_thread_report_progress(&s->ref->tf, y + ctb_size, 0);
        }
    } else if (s->threads_type & FF_THREAD_FRAME && x_end)
        ff_thread_report_progress(&s->ref->tf, y + ctb_size - 4, 0);
}