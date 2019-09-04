#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwCodingParamToolFlags; } ;
struct hevc_dxva2_picture_context {scalar_t__ slice_count; scalar_t__ bitstream_size; int /*<<< orphan*/  qm; TYPE_5__ pp; } ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {TYPE_1__* ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  frame; struct hevc_dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  commit_bitstream_and_slice_buffer ; 
 int ff_dxva2_common_end_frame (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxva2_hevc_end_frame(AVCodecContext *avctx)
{
    HEVCContext *h = avctx->priv_data;
    struct hevc_dxva2_picture_context *ctx_pic = h->ref->hwaccel_picture_private;
    int scale = ctx_pic->pp.dwCodingParamToolFlags & 1;
    int ret;

    if (ctx_pic->slice_count <= 0 || ctx_pic->bitstream_size <= 0)
        return -1;

    ret = ff_dxva2_common_end_frame(avctx, h->ref->frame,
                                    &ctx_pic->pp, sizeof(ctx_pic->pp),
                                    scale ? &ctx_pic->qm : NULL, scale ? sizeof(ctx_pic->qm) : 0,
                                    commit_bitstream_and_slice_buffer);
    return ret;
}