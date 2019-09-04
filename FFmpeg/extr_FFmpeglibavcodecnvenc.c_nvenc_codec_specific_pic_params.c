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
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  sliceModeData; int /*<<< orphan*/  sliceMode; } ;
struct TYPE_17__ {int /*<<< orphan*/  sliceModeData; int /*<<< orphan*/  sliceMode; } ;
struct TYPE_20__ {TYPE_4__ hevcConfig; TYPE_2__ h264Config; } ;
struct TYPE_21__ {TYPE_5__ encodeCodecConfig; } ;
struct TYPE_24__ {TYPE_6__ encode_config; } ;
struct TYPE_22__ {int seiPayloadArrayCnt; int /*<<< orphan*/ * seiPayloadArray; int /*<<< orphan*/  sliceModeData; int /*<<< orphan*/  sliceMode; } ;
struct TYPE_18__ {int seiPayloadArrayCnt; int /*<<< orphan*/ * seiPayloadArray; int /*<<< orphan*/  sliceModeData; int /*<<< orphan*/  sliceMode; } ;
struct TYPE_23__ {TYPE_7__ hevcPicParams; TYPE_3__ h264PicParams; } ;
struct TYPE_16__ {int id; } ;
struct TYPE_15__ {TYPE_1__* codec; TYPE_9__* priv_data; } ;
struct TYPE_14__ {TYPE_8__ codecPicParams; } ;
typedef  TYPE_9__ NvencContext ;
typedef  int /*<<< orphan*/  NV_ENC_SEI_PAYLOAD ;
typedef  TYPE_10__ NV_ENC_PIC_PARAMS ;
typedef  TYPE_11__ AVCodecContext ;

/* Variables and functions */
#define  AV_CODEC_ID_H264 129 
#define  AV_CODEC_ID_HEVC 128 

__attribute__((used)) static void nvenc_codec_specific_pic_params(AVCodecContext *avctx,
                                            NV_ENC_PIC_PARAMS *params,
                                            NV_ENC_SEI_PAYLOAD *sei_data)
{
    NvencContext *ctx = avctx->priv_data;

    switch (avctx->codec->id) {
    case AV_CODEC_ID_H264:
        params->codecPicParams.h264PicParams.sliceMode =
            ctx->encode_config.encodeCodecConfig.h264Config.sliceMode;
        params->codecPicParams.h264PicParams.sliceModeData =
            ctx->encode_config.encodeCodecConfig.h264Config.sliceModeData;
        if (sei_data) {
            params->codecPicParams.h264PicParams.seiPayloadArray = sei_data;
            params->codecPicParams.h264PicParams.seiPayloadArrayCnt = 1;
        }

      break;
    case AV_CODEC_ID_HEVC:
        params->codecPicParams.hevcPicParams.sliceMode =
            ctx->encode_config.encodeCodecConfig.hevcConfig.sliceMode;
        params->codecPicParams.hevcPicParams.sliceModeData =
            ctx->encode_config.encodeCodecConfig.hevcConfig.sliceModeData;
        if (sei_data) {
            params->codecPicParams.hevcPicParams.seiPayloadArray = sei_data;
            params->codecPicParams.hevcPicParams.seiPayloadArrayCnt = 1;
        }

        break;
    }
}