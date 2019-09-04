#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {int /*<<< orphan*/  sw_format; } ;
struct TYPE_25__ {int progressive_frame; int /*<<< orphan*/  output_stream; int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {scalar_t__ hwaccel_priv; } ;
struct TYPE_23__ {TYPE_4__* cudl; int /*<<< orphan*/  decoder; TYPE_3__* cvdl; int /*<<< orphan*/  cuda_ctx; int /*<<< orphan*/  stream; } ;
struct TYPE_22__ {TYPE_15__* decoder_ref; TYPE_15__* idx_ref; int /*<<< orphan*/  idx; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* cuvidUnmapVideoFrame ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* cuvidMapVideoFrame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,unsigned int*,TYPE_8__*) ;} ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_16__ {int* linesize; int height; int /*<<< orphan*/ * buf; int /*<<< orphan*/ ** data; TYPE_2__* hw_frames_ctx; TYPE_1__* private_ref; } ;
typedef  TYPE_5__ NVDECFrame ;
typedef  TYPE_6__ NVDECDecoder ;
typedef  TYPE_7__ FrameDecodeData ;
typedef  scalar_t__ CUdeviceptr ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_8__ CUVIDPROCPARAMS ;
typedef  TYPE_9__ AVHWFramesContext ;
typedef  TYPE_10__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* av_buffer_ref (TYPE_15__*) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 TYPE_5__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_pix_fmt_get_chroma_sub_sample (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  nvdec_unmap_mapped_frame ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,unsigned int*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvdec_retrieve_data(void *logctx, AVFrame *frame)
{
    FrameDecodeData  *fdd = (FrameDecodeData*)frame->private_ref->data;
    NVDECFrame        *cf = (NVDECFrame*)fdd->hwaccel_priv;
    NVDECDecoder *decoder = (NVDECDecoder*)cf->decoder_ref->data;

    AVHWFramesContext *hwctx = (AVHWFramesContext *)frame->hw_frames_ctx->data;

    CUVIDPROCPARAMS vpp = { 0 };
    NVDECFrame *unmap_data = NULL;

    CUcontext dummy;
    CUdeviceptr devptr;

    unsigned int pitch, i;
    unsigned int offset = 0;
    int shift_h = 0, shift_v = 0;
    int ret = 0;

    vpp.progressive_frame = 1;
    vpp.output_stream = decoder->stream;

    ret = CHECK_CU(decoder->cudl->cuCtxPushCurrent(decoder->cuda_ctx));
    if (ret < 0)
        return ret;

    ret = CHECK_CU(decoder->cvdl->cuvidMapVideoFrame(decoder->decoder,
                                                     cf->idx, &devptr,
                                                     &pitch, &vpp));
    if (ret < 0)
        goto finish;

    unmap_data = av_mallocz(sizeof(*unmap_data));
    if (!unmap_data) {
        ret = AVERROR(ENOMEM);
        goto copy_fail;
    }

    frame->buf[1] = av_buffer_create((uint8_t *)unmap_data, sizeof(*unmap_data),
                                     nvdec_unmap_mapped_frame, (void*)devptr,
                                     AV_BUFFER_FLAG_READONLY);
    if (!frame->buf[1]) {
        ret = AVERROR(ENOMEM);
        goto copy_fail;
    }

    unmap_data->idx = cf->idx;
    unmap_data->idx_ref = av_buffer_ref(cf->idx_ref);
    unmap_data->decoder_ref = av_buffer_ref(cf->decoder_ref);

    av_pix_fmt_get_chroma_sub_sample(hwctx->sw_format, &shift_h, &shift_v);
    for (i = 0; frame->linesize[i]; i++) {
        frame->data[i] = (uint8_t*)(devptr + offset);
        frame->linesize[i] = pitch;
        offset += pitch * (frame->height >> (i ? shift_v : 0));
    }

    goto finish;

copy_fail:
    if (!frame->buf[1]) {
        CHECK_CU(decoder->cvdl->cuvidUnmapVideoFrame(decoder->decoder, devptr));
        av_freep(&unmap_data);
    } else {
        av_buffer_unref(&frame->buf[1]);
    }

finish:
    CHECK_CU(decoder->cudl->cuCtxPopCurrent(&dummy));
    return ret;
}