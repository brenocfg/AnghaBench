#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* internal; } ;
struct TYPE_17__ {int /*<<< orphan*/  pSliceDataOffsets; int /*<<< orphan*/  nNumSlices; int /*<<< orphan*/  pBitstreamData; int /*<<< orphan*/  nBitstreamDataLen; } ;
struct TYPE_16__ {TYPE_7__ pic_params; int /*<<< orphan*/  slice_offsets; int /*<<< orphan*/  nb_slices; int /*<<< orphan*/  bitstream; int /*<<< orphan*/  bitstream_len; TYPE_2__* decoder_ref; } ;
struct TYPE_15__ {TYPE_4__* cudl; int /*<<< orphan*/  decoder; TYPE_3__* cvdl; int /*<<< orphan*/  cuda_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* cuvidDecodePicture ) (int /*<<< orphan*/ ,TYPE_7__*) ;} ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {TYPE_6__* hwaccel_priv_data; } ;
typedef  TYPE_5__ NVDECDecoder ;
typedef  TYPE_6__ NVDECContext ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_7__ CUVIDPICPARAMS ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

int ff_nvdec_end_frame(AVCodecContext *avctx)
{
    NVDECContext     *ctx = avctx->internal->hwaccel_priv_data;
    NVDECDecoder *decoder = (NVDECDecoder*)ctx->decoder_ref->data;
    void *logctx          = avctx;
    CUVIDPICPARAMS    *pp = &ctx->pic_params;

    CUcontext dummy;

    int ret = 0;

    pp->nBitstreamDataLen = ctx->bitstream_len;
    pp->pBitstreamData    = ctx->bitstream;
    pp->nNumSlices        = ctx->nb_slices;
    pp->pSliceDataOffsets = ctx->slice_offsets;

    ret = CHECK_CU(decoder->cudl->cuCtxPushCurrent(decoder->cuda_ctx));
    if (ret < 0)
        return ret;

    ret = CHECK_CU(decoder->cvdl->cuvidDecodePicture(decoder->decoder, &ctx->pic_params));
    if (ret < 0)
        goto finish;

finish:
    CHECK_CU(decoder->cudl->cuCtxPopCurrent(&dummy));

    return ret;
}