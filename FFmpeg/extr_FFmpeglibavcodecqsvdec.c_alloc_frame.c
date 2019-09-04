#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int NumExtParam; int /*<<< orphan*/ ** ExtParam; int /*<<< orphan*/ * MemId; scalar_t__ UV; scalar_t__ Y; int /*<<< orphan*/  PitchLow; } ;
struct TYPE_15__ {TYPE_1__ Data; int /*<<< orphan*/  Info; } ;
typedef  TYPE_4__ mfxFrameSurface1 ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_19__ {scalar_t__ format; scalar_t__* data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_18__ {int /*<<< orphan*/ * mids; } ;
struct TYPE_17__ {TYPE_7__ frames_ctx; int /*<<< orphan*/  frame_info; } ;
struct TYPE_13__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_14__ {TYPE_2__ Header; } ;
struct TYPE_16__ {int used; TYPE_3__ dec_info; int /*<<< orphan*/ * ext_param; TYPE_4__ surface; TYPE_9__* frame; } ;
typedef  TYPE_5__ QSVFrame ;
typedef  TYPE_6__ QSVContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 scalar_t__ AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  MFX_EXTBUFF_DECODED_FRAME_INFO ; 
 int ff_get_buffer (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int ff_qsv_find_surface_idx (TYPE_7__*,TYPE_5__*) ; 

__attribute__((used)) static int alloc_frame(AVCodecContext *avctx, QSVContext *q, QSVFrame *frame)
{
    int ret;

    ret = ff_get_buffer(avctx, frame->frame, AV_GET_BUFFER_FLAG_REF);
    if (ret < 0)
        return ret;

    if (frame->frame->format == AV_PIX_FMT_QSV) {
        frame->surface = *(mfxFrameSurface1*)frame->frame->data[3];
    } else {
        frame->surface.Info = q->frame_info;

        frame->surface.Data.PitchLow = frame->frame->linesize[0];
        frame->surface.Data.Y        = frame->frame->data[0];
        frame->surface.Data.UV       = frame->frame->data[1];
    }

    if (q->frames_ctx.mids) {
        ret = ff_qsv_find_surface_idx(&q->frames_ctx, frame);
        if (ret < 0)
            return ret;

        frame->surface.Data.MemId = &q->frames_ctx.mids[ret];
    }
    frame->surface.Data.ExtParam    = &frame->ext_param;
    frame->surface.Data.NumExtParam = 1;
    frame->ext_param                = (mfxExtBuffer*)&frame->dec_info;
    frame->dec_info.Header.BufferId = MFX_EXTBUFF_DECODED_FRAME_INFO;
    frame->dec_info.Header.BufferSz = sizeof(frame->dec_info);

    frame->used = 1;

    return 0;
}