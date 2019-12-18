#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_25__ {scalar_t__ (* nvEncReconfigureEncoder ) (int /*<<< orphan*/ ,TYPE_8__*) ;} ;
struct TYPE_22__ {int darWidth; int darHeight; TYPE_5__* encodeConfig; } ;
struct TYPE_24__ {int resetEncoder; int forceIDR; TYPE_6__ reInitEncodeParams; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {scalar_t__ vbvBufferSize; scalar_t__ maxBitRate; scalar_t__ averageBitRate; } ;
struct TYPE_19__ {TYPE_2__ rcParams; } ;
struct TYPE_17__ {TYPE_9__ nvenc_funcs; } ;
struct TYPE_23__ {scalar_t__ rc; TYPE_3__ encode_config; TYPE_6__ init_encode_params; int /*<<< orphan*/  nvencoder; scalar_t__ support_dyn_bitrate; TYPE_1__ nvenc_dload_funcs; } ;
struct TYPE_20__ {scalar_t__ vbvBufferSize; scalar_t__ maxBitRate; scalar_t__ averageBitRate; } ;
struct TYPE_21__ {TYPE_4__ rcParams; } ;
struct TYPE_16__ {scalar_t__ rc_buffer_size; scalar_t__ rc_max_rate; scalar_t__ bit_rate; TYPE_7__* priv_data; } ;
typedef  TYPE_7__ NvencContext ;
typedef  TYPE_8__ NV_ENC_RECONFIGURE_PARAMS ;
typedef  TYPE_9__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  scalar_t__ NVENCSTATUS ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_10__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ NV_ENC_PARAMS_RC_CONSTQP ; 
 int /*<<< orphan*/  NV_ENC_RECONFIGURE_PARAMS_VER ; 
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  compute_dar (TYPE_10__*,int*,int*) ; 
 int /*<<< orphan*/  nvenc_print_error (TYPE_10__*,scalar_t__,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_8__*) ; 

__attribute__((used)) static void reconfig_encoder(AVCodecContext *avctx, const AVFrame *frame)
{
    NvencContext *ctx = avctx->priv_data;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &ctx->nvenc_dload_funcs.nvenc_funcs;
    NVENCSTATUS ret;

    NV_ENC_RECONFIGURE_PARAMS params = { 0 };
    int needs_reconfig = 0;
    int needs_encode_config = 0;
    int reconfig_bitrate = 0, reconfig_dar = 0;
    int dw, dh;

    params.version = NV_ENC_RECONFIGURE_PARAMS_VER;
    params.reInitEncodeParams = ctx->init_encode_params;

    compute_dar(avctx, &dw, &dh);
    if (dw != ctx->init_encode_params.darWidth || dh != ctx->init_encode_params.darHeight) {
        av_log(avctx, AV_LOG_VERBOSE,
               "aspect ratio change (DAR): %d:%d -> %d:%d\n",
               ctx->init_encode_params.darWidth,
               ctx->init_encode_params.darHeight, dw, dh);

        params.reInitEncodeParams.darHeight = dh;
        params.reInitEncodeParams.darWidth = dw;

        needs_reconfig = 1;
        reconfig_dar = 1;
    }

    if (ctx->rc != NV_ENC_PARAMS_RC_CONSTQP && ctx->support_dyn_bitrate) {
        if (avctx->bit_rate > 0 && params.reInitEncodeParams.encodeConfig->rcParams.averageBitRate != avctx->bit_rate) {
            av_log(avctx, AV_LOG_VERBOSE,
                   "avg bitrate change: %d -> %d\n",
                   params.reInitEncodeParams.encodeConfig->rcParams.averageBitRate,
                   (uint32_t)avctx->bit_rate);

            params.reInitEncodeParams.encodeConfig->rcParams.averageBitRate = avctx->bit_rate;
            reconfig_bitrate = 1;
        }

        if (avctx->rc_max_rate > 0 && ctx->encode_config.rcParams.maxBitRate != avctx->rc_max_rate) {
            av_log(avctx, AV_LOG_VERBOSE,
                   "max bitrate change: %d -> %d\n",
                   params.reInitEncodeParams.encodeConfig->rcParams.maxBitRate,
                   (uint32_t)avctx->rc_max_rate);

            params.reInitEncodeParams.encodeConfig->rcParams.maxBitRate = avctx->rc_max_rate;
            reconfig_bitrate = 1;
        }

        if (avctx->rc_buffer_size > 0 && ctx->encode_config.rcParams.vbvBufferSize != avctx->rc_buffer_size) {
            av_log(avctx, AV_LOG_VERBOSE,
                   "vbv buffer size change: %d -> %d\n",
                   params.reInitEncodeParams.encodeConfig->rcParams.vbvBufferSize,
                   avctx->rc_buffer_size);

            params.reInitEncodeParams.encodeConfig->rcParams.vbvBufferSize = avctx->rc_buffer_size;
            reconfig_bitrate = 1;
        }

        if (reconfig_bitrate) {
            params.resetEncoder = 1;
            params.forceIDR = 1;

            needs_encode_config = 1;
            needs_reconfig = 1;
        }
    }

    if (!needs_encode_config)
        params.reInitEncodeParams.encodeConfig = NULL;

    if (needs_reconfig) {
        ret = p_nvenc->nvEncReconfigureEncoder(ctx->nvencoder, &params);
        if (ret != NV_ENC_SUCCESS) {
            nvenc_print_error(avctx, ret, "failed to reconfigure nvenc");
        } else {
            if (reconfig_dar) {
                ctx->init_encode_params.darHeight = dh;
                ctx->init_encode_params.darWidth = dw;
            }

            if (reconfig_bitrate) {
                ctx->encode_config.rcParams.averageBitRate = params.reInitEncodeParams.encodeConfig->rcParams.averageBitRate;
                ctx->encode_config.rcParams.maxBitRate = params.reInitEncodeParams.encodeConfig->rcParams.maxBitRate;
                ctx->encode_config.rcParams.vbvBufferSize = params.reInitEncodeParams.encodeConfig->rcParams.vbvBufferSize;
            }

        }
    }
}