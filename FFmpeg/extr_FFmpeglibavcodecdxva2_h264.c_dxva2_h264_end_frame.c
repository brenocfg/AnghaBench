#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dxva2_picture_context {scalar_t__ slice_count; scalar_t__ bitstream_size; int /*<<< orphan*/  qm; int /*<<< orphan*/  pp; } ;
struct TYPE_11__ {TYPE_3__* priv_data; } ;
struct TYPE_10__ {TYPE_2__* avctx; TYPE_1__* cur_pic_ptr; int /*<<< orphan*/ * slice_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; } ;
struct TYPE_8__ {int /*<<< orphan*/  f; struct dxva2_picture_context* hwaccel_picture_private; } ;
typedef  int /*<<< orphan*/  H264SliceContext ;
typedef  TYPE_3__ H264Context ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  commit_bitstream_and_slice_buffer ; 
 int ff_dxva2_common_end_frame (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_h264_draw_horiz_band (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxva2_h264_end_frame(AVCodecContext *avctx)
{
    H264Context *h = avctx->priv_data;
    H264SliceContext *sl = &h->slice_ctx[0];
    struct dxva2_picture_context *ctx_pic =
        h->cur_pic_ptr->hwaccel_picture_private;
    int ret;

    if (ctx_pic->slice_count <= 0 || ctx_pic->bitstream_size <= 0)
        return -1;
    ret = ff_dxva2_common_end_frame(avctx, h->cur_pic_ptr->f,
                                    &ctx_pic->pp, sizeof(ctx_pic->pp),
                                    &ctx_pic->qm, sizeof(ctx_pic->qm),
                                    commit_bitstream_and_slice_buffer);
    if (!ret)
        ff_h264_draw_horiz_band(h, sl, 0, h->avctx->height);
    return ret;
}