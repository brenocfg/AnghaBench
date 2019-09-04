#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ pix_fmt; TYPE_4__* priv_data; } ;
struct TYPE_23__ {scalar_t__* data; int /*<<< orphan*/ * linesize; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/  sw_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_21__ {int (* nvEncRegisterResource ) (int /*<<< orphan*/ ,TYPE_5__*) ;} ;
struct TYPE_20__ {scalar_t__ resourceToRegister; intptr_t subResourceIndex; scalar_t__ bufferFormat; int /*<<< orphan*/  registeredResource; int /*<<< orphan*/  resourceType; int /*<<< orphan*/  pitch; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  version; } ;
struct TYPE_18__ {TYPE_6__ nvenc_funcs; } ;
struct TYPE_19__ {int nb_registered_frames; TYPE_2__* registered_frames; int /*<<< orphan*/  nvencoder; TYPE_3__ nvenc_dload_funcs; } ;
struct TYPE_17__ {scalar_t__ ptr; intptr_t ptr_index; int /*<<< orphan*/  regptr; } ;
struct TYPE_16__ {scalar_t__ data; } ;
typedef  TYPE_3__ NvencDynLoadFunctions ;
typedef  TYPE_4__ NvencContext ;
typedef  TYPE_5__ NV_ENC_REGISTER_RESOURCE ;
typedef  TYPE_6__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 scalar_t__ AV_PIX_FMT_CUDA ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ NV_ENC_BUFFER_FORMAT_UNDEFINED ; 
 int /*<<< orphan*/  NV_ENC_INPUT_RESOURCE_TYPE_CUDADEVICEPTR ; 
 int /*<<< orphan*/  NV_ENC_INPUT_RESOURCE_TYPE_DIRECTX ; 
 int /*<<< orphan*/  NV_ENC_REGISTER_RESOURCE_VER ; 
 int NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nvenc_find_free_reg_resource (TYPE_9__*) ; 
 scalar_t__ nvenc_map_buffer_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvenc_print_error (TYPE_9__*,int,char*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int nvenc_register_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    NvencContext *ctx = avctx->priv_data;
    NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;

    AVHWFramesContext *frames_ctx = (AVHWFramesContext*)frame->hw_frames_ctx->data;
    NV_ENC_REGISTER_RESOURCE reg;
    int i, idx, ret;

    for (i = 0; i < ctx->nb_registered_frames; i++) {
        if (avctx->pix_fmt == AV_PIX_FMT_CUDA && ctx->registered_frames[i].ptr == frame->data[0])
            return i;
        else if (avctx->pix_fmt == AV_PIX_FMT_D3D11 && ctx->registered_frames[i].ptr == frame->data[0] && ctx->registered_frames[i].ptr_index == (intptr_t)frame->data[1])
            return i;
    }

    idx = nvenc_find_free_reg_resource(avctx);
    if (idx < 0)
        return idx;

    reg.version            = NV_ENC_REGISTER_RESOURCE_VER;
    reg.width              = frames_ctx->width;
    reg.height             = frames_ctx->height;
    reg.pitch              = frame->linesize[0];
    reg.resourceToRegister = frame->data[0];

    if (avctx->pix_fmt == AV_PIX_FMT_CUDA) {
        reg.resourceType   = NV_ENC_INPUT_RESOURCE_TYPE_CUDADEVICEPTR;
    }
    else if (avctx->pix_fmt == AV_PIX_FMT_D3D11) {
        reg.resourceType     = NV_ENC_INPUT_RESOURCE_TYPE_DIRECTX;
        reg.subResourceIndex = (intptr_t)frame->data[1];
    }

    reg.bufferFormat       = nvenc_map_buffer_format(frames_ctx->sw_format);
    if (reg.bufferFormat == NV_ENC_BUFFER_FORMAT_UNDEFINED) {
        av_log(avctx, AV_LOG_FATAL, "Invalid input pixel format: %s\n",
               av_get_pix_fmt_name(frames_ctx->sw_format));
        return AVERROR(EINVAL);
    }

    ret = p_nvenc->nvEncRegisterResource(ctx->nvencoder, &reg);
    if (ret != NV_ENC_SUCCESS) {
        nvenc_print_error(avctx, ret, "Error registering an input resource");
        return AVERROR_UNKNOWN;
    }

    ctx->registered_frames[idx].ptr       = frame->data[0];
    ctx->registered_frames[idx].ptr_index = reg.subResourceIndex;
    ctx->registered_frames[idx].regptr    = reg.registeredResource;
    return idx;
}