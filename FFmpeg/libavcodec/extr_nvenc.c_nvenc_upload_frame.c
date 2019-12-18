#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ pix_fmt; TYPE_4__* priv_data; } ;
struct TYPE_30__ {int /*<<< orphan*/ * linesize; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* nvEncUnlockInputBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* nvEncLockInputBuffer ) (int /*<<< orphan*/ ,TYPE_5__*) ;int /*<<< orphan*/  (* nvEncMapInputResource ) (int /*<<< orphan*/ ,TYPE_10__*) ;} ;
struct TYPE_28__ {int /*<<< orphan*/  pitch; int /*<<< orphan*/  inputBuffer; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
struct TYPE_26__ {TYPE_6__ nvenc_funcs; } ;
struct TYPE_27__ {int /*<<< orphan*/  nvencoder; TYPE_1__* registered_frames; TYPE_3__ nvenc_dload_funcs; } ;
struct TYPE_25__ {int reg_idx; int /*<<< orphan*/  input_surface; int /*<<< orphan*/  pitch; int /*<<< orphan*/  format; int /*<<< orphan*/  in_ref; } ;
struct TYPE_23__ {int /*<<< orphan*/  mappedBufferFmt; int /*<<< orphan*/  mappedResource; int /*<<< orphan*/  registeredResource; int /*<<< orphan*/  version; } ;
struct TYPE_24__ {TYPE_10__ in_map; scalar_t__ mapped; int /*<<< orphan*/  regptr; } ;
typedef  TYPE_2__ NvencSurface ;
typedef  TYPE_3__ NvencDynLoadFunctions ;
typedef  TYPE_4__ NvencContext ;
typedef  TYPE_5__ NV_ENC_LOCK_INPUT_BUFFER ;
typedef  TYPE_6__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  int /*<<< orphan*/  NVENCSTATUS ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_CUDA ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 int /*<<< orphan*/  NV_ENC_LOCK_INPUT_BUFFER_VER ; 
 int /*<<< orphan*/  NV_ENC_MAP_INPUT_RESOURCE_VER ; 
 int /*<<< orphan*/  NV_ENC_SUCCESS ; 
 int av_frame_ref (int /*<<< orphan*/ ,TYPE_7__ const*) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int nvenc_copy_frame (TYPE_8__*,TYPE_2__*,TYPE_5__*,TYPE_7__ const*) ; 
 int nvenc_print_error (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int nvenc_register_frame (TYPE_8__*,TYPE_7__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvenc_upload_frame(AVCodecContext *avctx, const AVFrame *frame,
                                      NvencSurface *nvenc_frame)
{
    NvencContext *ctx = avctx->priv_data;
    NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;

    int res;
    NVENCSTATUS nv_status;

    if (avctx->pix_fmt == AV_PIX_FMT_CUDA || avctx->pix_fmt == AV_PIX_FMT_D3D11) {
        int reg_idx = nvenc_register_frame(avctx, frame);
        if (reg_idx < 0) {
            av_log(avctx, AV_LOG_ERROR, "Could not register an input HW frame\n");
            return reg_idx;
        }

        res = av_frame_ref(nvenc_frame->in_ref, frame);
        if (res < 0)
            return res;

        if (!ctx->registered_frames[reg_idx].mapped) {
            ctx->registered_frames[reg_idx].in_map.version = NV_ENC_MAP_INPUT_RESOURCE_VER;
            ctx->registered_frames[reg_idx].in_map.registeredResource = ctx->registered_frames[reg_idx].regptr;
            nv_status = p_nvenc->nvEncMapInputResource(ctx->nvencoder, &ctx->registered_frames[reg_idx].in_map);
            if (nv_status != NV_ENC_SUCCESS) {
                av_frame_unref(nvenc_frame->in_ref);
                return nvenc_print_error(avctx, nv_status, "Error mapping an input resource");
            }
        }

        ctx->registered_frames[reg_idx].mapped += 1;

        nvenc_frame->reg_idx                   = reg_idx;
        nvenc_frame->input_surface             = ctx->registered_frames[reg_idx].in_map.mappedResource;
        nvenc_frame->format                    = ctx->registered_frames[reg_idx].in_map.mappedBufferFmt;
        nvenc_frame->pitch                     = frame->linesize[0];

        return 0;
    } else {
        NV_ENC_LOCK_INPUT_BUFFER lockBufferParams = { 0 };

        lockBufferParams.version = NV_ENC_LOCK_INPUT_BUFFER_VER;
        lockBufferParams.inputBuffer = nvenc_frame->input_surface;

        nv_status = p_nvenc->nvEncLockInputBuffer(ctx->nvencoder, &lockBufferParams);
        if (nv_status != NV_ENC_SUCCESS) {
            return nvenc_print_error(avctx, nv_status, "Failed locking nvenc input buffer");
        }

        nvenc_frame->pitch = lockBufferParams.pitch;
        res = nvenc_copy_frame(avctx, nvenc_frame, &lockBufferParams, frame);

        nv_status = p_nvenc->nvEncUnlockInputBuffer(ctx->nvencoder, nvenc_frame->input_surface);
        if (nv_status != NV_ENC_SUCCESS) {
            return nvenc_print_error(avctx, nv_status, "Failed unlocking input buffer!");
        }

        return res;
    }
}