#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  enum AVPictureType { ____Placeholder_AVPictureType } AVPictureType ;
struct TYPE_29__ {scalar_t__ (* nvEncLockBitstream ) (int /*<<< orphan*/ ,TYPE_11__*) ;scalar_t__ (* nvEncUnlockBitstream ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* nvEncUnmapInputResource ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_40__ {TYPE_12__ nvenc_funcs; } ;
struct TYPE_39__ {size_t reg_idx; int /*<<< orphan*/ * input_surface; int /*<<< orphan*/  in_ref; int /*<<< orphan*/  output_surface; } ;
struct TYPE_37__ {int /*<<< orphan*/  mappedResource; } ;
struct TYPE_38__ {scalar_t__ mapped; TYPE_6__ in_map; } ;
struct TYPE_34__ {int sliceModeData; } ;
struct TYPE_33__ {int sliceModeData; } ;
struct TYPE_35__ {TYPE_3__ hevcConfig; TYPE_2__ h264Config; } ;
struct TYPE_36__ {TYPE_4__ encodeCodecConfig; } ;
struct TYPE_32__ {int id; } ;
struct TYPE_31__ {scalar_t__ pix_fmt; TYPE_1__* codec; TYPE_10__* priv_data; } ;
struct TYPE_30__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {int* sliceOffsets; int pictureType; int frameAvgQP; int /*<<< orphan*/  bitstreamSizeInBytes; int /*<<< orphan*/  bitstreamBufferPtr; int /*<<< orphan*/  outputBitstream; scalar_t__ doNotWait; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
struct TYPE_27__ {int /*<<< orphan*/  timestamp_list; TYPE_7__* registered_frames; int /*<<< orphan*/  nvencoder; TYPE_5__ encode_config; TYPE_9__ nvenc_dload_funcs; } ;
typedef  TYPE_8__ NvencSurface ;
typedef  TYPE_9__ NvencDynLoadFunctions ;
typedef  TYPE_10__ NvencContext ;
typedef  TYPE_11__ NV_ENC_LOCK_BITSTREAM ;
typedef  TYPE_12__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  scalar_t__ NVENCSTATUS ;
typedef  TYPE_13__ AVPacket ;
typedef  TYPE_14__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int AVERROR_EXTERNAL ; 
#define  AV_CODEC_ID_H264 134 
#define  AV_CODEC_ID_H265 133 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_BI ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_P ; 
 scalar_t__ AV_PIX_FMT_CUDA ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_QP2LAMBDA ; 
 int /*<<< orphan*/  NV_ENC_LOCK_BITSTREAM_VER ; 
#define  NV_ENC_PIC_TYPE_B 132 
#define  NV_ENC_PIC_TYPE_BI 131 
#define  NV_ENC_PIC_TYPE_I 130 
#define  NV_ENC_PIC_TYPE_IDR 129 
#define  NV_ENC_PIC_TYPE_P 128 
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_14__*,int /*<<< orphan*/ ,char*) ; 
 int* av_mallocz (int) ; 
 int ff_alloc_packet2 (TYPE_14__*,TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_13__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvenc_print_error (TYPE_14__*,scalar_t__,char*) ; 
 int nvenc_set_timestamp (TYPE_14__*,TYPE_11__*,TYPE_13__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_11__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamp_queue_dequeue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_output_surface(AVCodecContext *avctx, AVPacket *pkt, NvencSurface *tmpoutsurf)
{
    NvencContext *ctx = avctx->priv_data;
    NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;

    uint32_t slice_mode_data;
    uint32_t *slice_offsets = NULL;
    NV_ENC_LOCK_BITSTREAM lock_params = { 0 };
    NVENCSTATUS nv_status;
    int res = 0;

    enum AVPictureType pict_type;

    switch (avctx->codec->id) {
    case AV_CODEC_ID_H264:
      slice_mode_data = ctx->encode_config.encodeCodecConfig.h264Config.sliceModeData;
      break;
    case AV_CODEC_ID_H265:
      slice_mode_data = ctx->encode_config.encodeCodecConfig.hevcConfig.sliceModeData;
      break;
    default:
      av_log(avctx, AV_LOG_ERROR, "Unknown codec name\n");
      res = AVERROR(EINVAL);
      goto error;
    }
    slice_offsets = av_mallocz(slice_mode_data * sizeof(*slice_offsets));

    if (!slice_offsets) {
        res = AVERROR(ENOMEM);
        goto error;
    }

    lock_params.version = NV_ENC_LOCK_BITSTREAM_VER;

    lock_params.doNotWait = 0;
    lock_params.outputBitstream = tmpoutsurf->output_surface;
    lock_params.sliceOffsets = slice_offsets;

    nv_status = p_nvenc->nvEncLockBitstream(ctx->nvencoder, &lock_params);
    if (nv_status != NV_ENC_SUCCESS) {
        res = nvenc_print_error(avctx, nv_status, "Failed locking bitstream buffer");
        goto error;
    }

    if (res = ff_alloc_packet2(avctx, pkt, lock_params.bitstreamSizeInBytes,0)) {
        p_nvenc->nvEncUnlockBitstream(ctx->nvencoder, tmpoutsurf->output_surface);
        goto error;
    }

    memcpy(pkt->data, lock_params.bitstreamBufferPtr, lock_params.bitstreamSizeInBytes);

    nv_status = p_nvenc->nvEncUnlockBitstream(ctx->nvencoder, tmpoutsurf->output_surface);
    if (nv_status != NV_ENC_SUCCESS) {
        res = nvenc_print_error(avctx, nv_status, "Failed unlocking bitstream buffer, expect the gates of mordor to open");
        goto error;
    }


    if (avctx->pix_fmt == AV_PIX_FMT_CUDA || avctx->pix_fmt == AV_PIX_FMT_D3D11) {
        ctx->registered_frames[tmpoutsurf->reg_idx].mapped -= 1;
        if (ctx->registered_frames[tmpoutsurf->reg_idx].mapped == 0) {
            nv_status = p_nvenc->nvEncUnmapInputResource(ctx->nvencoder, ctx->registered_frames[tmpoutsurf->reg_idx].in_map.mappedResource);
            if (nv_status != NV_ENC_SUCCESS) {
                res = nvenc_print_error(avctx, nv_status, "Failed unmapping input resource");
                goto error;
            }
        } else if (ctx->registered_frames[tmpoutsurf->reg_idx].mapped < 0) {
            res = AVERROR_BUG;
            goto error;
        }

        av_frame_unref(tmpoutsurf->in_ref);

        tmpoutsurf->input_surface = NULL;
    }

    switch (lock_params.pictureType) {
    case NV_ENC_PIC_TYPE_IDR:
        pkt->flags |= AV_PKT_FLAG_KEY;
    case NV_ENC_PIC_TYPE_I:
        pict_type = AV_PICTURE_TYPE_I;
        break;
    case NV_ENC_PIC_TYPE_P:
        pict_type = AV_PICTURE_TYPE_P;
        break;
    case NV_ENC_PIC_TYPE_B:
        pict_type = AV_PICTURE_TYPE_B;
        break;
    case NV_ENC_PIC_TYPE_BI:
        pict_type = AV_PICTURE_TYPE_BI;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown picture type encountered, expect the output to be broken.\n");
        av_log(avctx, AV_LOG_ERROR, "Please report this error and include as much information on how to reproduce it as possible.\n");
        res = AVERROR_EXTERNAL;
        goto error;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->pict_type = pict_type;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    ff_side_data_set_encoder_stats(pkt,
        (lock_params.frameAvgQP - 1) * FF_QP2LAMBDA, NULL, 0, pict_type);

    res = nvenc_set_timestamp(avctx, &lock_params, pkt);
    if (res < 0)
        goto error2;

    av_free(slice_offsets);

    return 0;

error:
    timestamp_queue_dequeue(ctx->timestamp_list);

error2:
    av_free(slice_offsets);

    return res;
}