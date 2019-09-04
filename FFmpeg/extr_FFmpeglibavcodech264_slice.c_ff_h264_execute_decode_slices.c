#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_4__* const,int (*) (TYPE_4__* const,TYPE_2__*),TYPE_2__*,int /*<<< orphan*/ *,int,int) ;scalar_t__ hwaccel; } ;
struct TYPE_17__ {int nb_slice_ctx_queued; int mb_height; int mb_width; int mb_y; TYPE_2__* slice_ctx; scalar_t__ postpone_filter; TYPE_4__* avctx; } ;
struct TYPE_15__ {scalar_t__ error_count; } ;
struct TYPE_16__ {int next_slice_idx; int mb_y; int mb_x; int resync_mb_y; int /*<<< orphan*/  resync_mb_x; TYPE_1__ er; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ CONFIG_ERROR_RESILIENCE ; 
 int FFMIN (int,int) ; 
 scalar_t__ FIELD_OR_MBAFF_PICTURE (TYPE_3__*) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int decode_slice (TYPE_4__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  loop_filter (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__* const,int (*) (TYPE_4__* const,TYPE_2__*),TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 

int ff_h264_execute_decode_slices(H264Context *h)
{
    AVCodecContext *const avctx = h->avctx;
    H264SliceContext *sl;
    int context_count = h->nb_slice_ctx_queued;
    int ret = 0;
    int i, j;

    h->slice_ctx[0].next_slice_idx = INT_MAX;

    if (h->avctx->hwaccel || context_count < 1)
        return 0;

    av_assert0(context_count && h->slice_ctx[context_count - 1].mb_y < h->mb_height);

    if (context_count == 1) {

        h->slice_ctx[0].next_slice_idx = h->mb_width * h->mb_height;
        h->postpone_filter = 0;

        ret = decode_slice(avctx, &h->slice_ctx[0]);
        h->mb_y = h->slice_ctx[0].mb_y;
        if (ret < 0)
            goto finish;
    } else {
        av_assert0(context_count > 0);
        for (i = 0; i < context_count; i++) {
            int next_slice_idx = h->mb_width * h->mb_height;
            int slice_idx;

            sl                 = &h->slice_ctx[i];
            if (CONFIG_ERROR_RESILIENCE) {
                sl->er.error_count = 0;
            }

            /* make sure none of those slices overlap */
            slice_idx = sl->mb_y * h->mb_width + sl->mb_x;
            for (j = 0; j < context_count; j++) {
                H264SliceContext *sl2 = &h->slice_ctx[j];
                int        slice_idx2 = sl2->mb_y * h->mb_width + sl2->mb_x;

                if (i == j || slice_idx2 < slice_idx)
                    continue;
                next_slice_idx = FFMIN(next_slice_idx, slice_idx2);
            }
            sl->next_slice_idx = next_slice_idx;
        }

        avctx->execute(avctx, decode_slice, h->slice_ctx,
                       NULL, context_count, sizeof(h->slice_ctx[0]));

        /* pull back stuff from slices to master context */
        sl                   = &h->slice_ctx[context_count - 1];
        h->mb_y              = sl->mb_y;
        if (CONFIG_ERROR_RESILIENCE) {
            for (i = 1; i < context_count; i++)
                h->slice_ctx[0].er.error_count += h->slice_ctx[i].er.error_count;
        }

        if (h->postpone_filter) {
            h->postpone_filter = 0;

            for (i = 0; i < context_count; i++) {
                int y_end, x_end;

                sl = &h->slice_ctx[i];
                y_end = FFMIN(sl->mb_y + 1, h->mb_height);
                x_end = (sl->mb_y >= h->mb_height) ? h->mb_width : sl->mb_x;

                for (j = sl->resync_mb_y; j < y_end; j += 1 + FIELD_OR_MBAFF_PICTURE(h)) {
                    sl->mb_y = j;
                    loop_filter(h, sl, j > sl->resync_mb_y ? 0 : sl->resync_mb_x,
                                j == y_end - 1 ? x_end : h->mb_width);
                }
            }
        }
    }

finish:
    h->nb_slice_ctx_queued = 0;
    return ret;
}