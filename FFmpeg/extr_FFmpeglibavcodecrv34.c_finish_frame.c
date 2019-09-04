#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  f; int /*<<< orphan*/  tf; } ;
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {scalar_t__ pict_type; TYPE_7__* last_picture_ptr; TYPE_7__* current_picture_ptr; scalar_t__ low_delay; TYPE_1__* avctx; scalar_t__ mb_num_left; int /*<<< orphan*/  er; } ;
struct TYPE_12__ {TYPE_3__ s; } ;
struct TYPE_11__ {int active_thread_type; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  FF_QSCALE_TYPE_MPEG1 ; 
 int FF_THREAD_FRAME ; 
 scalar_t__ HAVE_THREADS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_er_frame_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mpv_export_qp_table (TYPE_3__*,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpv_frame_end (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_print_debug_info (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int finish_frame(AVCodecContext *avctx, AVFrame *pict)
{
    RV34DecContext *r = avctx->priv_data;
    MpegEncContext *s = &r->s;
    int got_picture = 0, ret;

    ff_er_frame_end(&s->er);
    ff_mpv_frame_end(s);
    s->mb_num_left = 0;

    if (HAVE_THREADS && (s->avctx->active_thread_type & FF_THREAD_FRAME))
        ff_thread_report_progress(&s->current_picture_ptr->tf, INT_MAX, 0);

    if (s->pict_type == AV_PICTURE_TYPE_B || s->low_delay) {
        if ((ret = av_frame_ref(pict, s->current_picture_ptr->f)) < 0)
            return ret;
        ff_print_debug_info(s, s->current_picture_ptr, pict);
        ff_mpv_export_qp_table(s, pict, s->current_picture_ptr, FF_QSCALE_TYPE_MPEG1);
        got_picture = 1;
    } else if (s->last_picture_ptr) {
        if ((ret = av_frame_ref(pict, s->last_picture_ptr->f)) < 0)
            return ret;
        ff_print_debug_info(s, s->last_picture_ptr, pict);
        ff_mpv_export_qp_table(s, pict, s->last_picture_ptr, FF_QSCALE_TYPE_MPEG1);
        got_picture = 1;
    }

    return got_picture;
}