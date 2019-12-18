#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_22__ {scalar_t__ data; } ;
struct TYPE_21__ {int /*<<< orphan*/  stream; TYPE_1__* internal; int /*<<< orphan*/  cuda_ctx; } ;
struct TYPE_20__ {TYPE_5__* hwctx; } ;
struct TYPE_19__ {TYPE_2__* cudl; int /*<<< orphan*/  decoder; TYPE_10__* cvdl; int /*<<< orphan*/  cuda_ctx; int /*<<< orphan*/  stream; int /*<<< orphan*/  hw_device_ref; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_2__* cuda_dl; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* cuvidCreateDecoder ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ NVDECDecoder ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  int /*<<< orphan*/  CUVIDDECODECREATEINFO ;
typedef  TYPE_4__ AVHWDeviceContext ;
typedef  TYPE_5__ AVCUDADeviceContext ;
typedef  TYPE_6__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_6__* av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_ref (TYPE_6__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_6__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* av_mallocz (int) ; 
 int cuvid_load_functions (TYPE_10__**,void*) ; 
 int /*<<< orphan*/  nvdec_decoder_free ; 
 int nvdec_test_capabilities (TYPE_3__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvdec_decoder_create(AVBufferRef **out, AVBufferRef *hw_device_ref,
                                CUVIDDECODECREATEINFO *params, void *logctx)
{
    AVHWDeviceContext  *hw_device_ctx = (AVHWDeviceContext*)hw_device_ref->data;
    AVCUDADeviceContext *device_hwctx = hw_device_ctx->hwctx;

    AVBufferRef *decoder_ref;
    NVDECDecoder *decoder;

    CUcontext dummy;
    int ret;

    decoder = av_mallocz(sizeof(*decoder));
    if (!decoder)
        return AVERROR(ENOMEM);

    decoder_ref = av_buffer_create((uint8_t*)decoder, sizeof(*decoder),
                                   nvdec_decoder_free, NULL, AV_BUFFER_FLAG_READONLY);
    if (!decoder_ref) {
        av_freep(&decoder);
        return AVERROR(ENOMEM);
    }

    decoder->hw_device_ref = av_buffer_ref(hw_device_ref);
    if (!decoder->hw_device_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    decoder->cuda_ctx = device_hwctx->cuda_ctx;
    decoder->cudl = device_hwctx->internal->cuda_dl;
    decoder->stream = device_hwctx->stream;

    ret = cuvid_load_functions(&decoder->cvdl, logctx);
    if (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Failed loading nvcuvid.\n");
        goto fail;
    }

    ret = CHECK_CU(decoder->cudl->cuCtxPushCurrent(decoder->cuda_ctx));
    if (ret < 0)
        goto fail;

    ret = nvdec_test_capabilities(decoder, params, logctx);
    if (ret < 0) {
        CHECK_CU(decoder->cudl->cuCtxPopCurrent(&dummy));
        goto fail;
    }

    ret = CHECK_CU(decoder->cvdl->cuvidCreateDecoder(&decoder->decoder, params));

    CHECK_CU(decoder->cudl->cuCtxPopCurrent(&dummy));

    if (ret < 0) {
        goto fail;
    }

    *out = decoder_ref;

    return 0;
fail:
    av_buffer_unref(&decoder_ref);
    return ret;
}