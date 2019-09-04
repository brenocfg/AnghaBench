#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int active_thread_type; int const skip_top; int /*<<< orphan*/  error_concealment; TYPE_1__* hwaccel; } ;
struct TYPE_7__ {int mb_width; int mb_num; int* mb_index2xy; int error_occurred; int* error_status_table; int /*<<< orphan*/  error_count; TYPE_5__* avctx; } ;
struct TYPE_6__ {scalar_t__ decode_slice; } ;
typedef  TYPE_2__ ERContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int ER_AC_END ; 
 int ER_AC_ERROR ; 
 int ER_DC_END ; 
 int ER_DC_ERROR ; 
 int ER_MB_ERROR ; 
 int ER_MV_END ; 
 int ER_MV_ERROR ; 
 int FF_THREAD_SLICE ; 
 int /*<<< orphan*/  INT_MAX ; 
 int VP_START ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ er_supported (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int const) ; 

void ff_er_add_slice(ERContext *s, int startx, int starty,
                     int endx, int endy, int status)
{
    const int start_i  = av_clip(startx + starty * s->mb_width, 0, s->mb_num - 1);
    const int end_i    = av_clip(endx   + endy   * s->mb_width, 0, s->mb_num);
    const int start_xy = s->mb_index2xy[start_i];
    const int end_xy   = s->mb_index2xy[end_i];
    int mask           = -1;

    if (s->avctx->hwaccel && s->avctx->hwaccel->decode_slice)
        return;

    if (start_i > end_i || start_xy > end_xy) {
        av_log(s->avctx, AV_LOG_ERROR,
               "internal error, slice end before start\n");
        return;
    }

    if (!s->avctx->error_concealment)
        return;

    mask &= ~VP_START;
    if (status & (ER_AC_ERROR | ER_AC_END)) {
        mask           &= ~(ER_AC_ERROR | ER_AC_END);
        atomic_fetch_add(&s->error_count, start_i - end_i - 1);
    }
    if (status & (ER_DC_ERROR | ER_DC_END)) {
        mask           &= ~(ER_DC_ERROR | ER_DC_END);
        atomic_fetch_add(&s->error_count, start_i - end_i - 1);
    }
    if (status & (ER_MV_ERROR | ER_MV_END)) {
        mask           &= ~(ER_MV_ERROR | ER_MV_END);
        atomic_fetch_add(&s->error_count, start_i - end_i - 1);
    }

    if (status & ER_MB_ERROR) {
        s->error_occurred = 1;
        atomic_store(&s->error_count, INT_MAX);
    }

    if (mask == ~0x7F) {
        memset(&s->error_status_table[start_xy], 0,
               (end_xy - start_xy) * sizeof(uint8_t));
    } else {
        int i;
        for (i = start_xy; i < end_xy; i++)
            s->error_status_table[i] &= mask;
    }

    if (end_i == s->mb_num)
        atomic_store(&s->error_count, INT_MAX);
    else {
        s->error_status_table[end_xy] &= mask;
        s->error_status_table[end_xy] |= status;
    }

    s->error_status_table[start_xy] |= VP_START;

    if (start_xy > 0 && !(s->avctx->active_thread_type & FF_THREAD_SLICE) &&
        er_supported(s) && s->avctx->skip_top * s->mb_width < start_i) {
        int prev_status = s->error_status_table[s->mb_index2xy[start_i - 1]];

        prev_status &= ~ VP_START;
        if (prev_status != (ER_MV_END | ER_DC_END | ER_AC_END)) {
            s->error_occurred = 1;
            atomic_store(&s->error_count, INT_MAX);
        }
    }
}