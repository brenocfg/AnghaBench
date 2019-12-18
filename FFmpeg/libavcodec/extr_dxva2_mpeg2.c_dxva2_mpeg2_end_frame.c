#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dxva2_picture_context {scalar_t__ slice_count; scalar_t__ bitstream_size; int /*<<< orphan*/  qm; int /*<<< orphan*/  pp; } ;
struct MpegEncContext {TYPE_1__* current_picture_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; struct MpegEncContext* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  f; struct dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  commit_bitstream_and_slice_buffer ; 
 int ff_dxva2_common_end_frame (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpeg_draw_horiz_band (struct MpegEncContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxva2_mpeg2_end_frame(AVCodecContext *avctx)
{
    struct MpegEncContext *s = avctx->priv_data;
    struct dxva2_picture_context *ctx_pic =
        s->current_picture_ptr->hwaccel_picture_private;
    int ret;

    if (ctx_pic->slice_count <= 0 || ctx_pic->bitstream_size <= 0)
        return -1;
    ret = ff_dxva2_common_end_frame(avctx, s->current_picture_ptr->f,
                                    &ctx_pic->pp, sizeof(ctx_pic->pp),
                                    &ctx_pic->qm, sizeof(ctx_pic->qm),
                                    commit_bitstream_and_slice_buffer);
    if (!ret)
        ff_mpeg_draw_horiz_band(s, 0, avctx->height);
    return ret;
}