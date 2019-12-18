#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_23__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vps_buf ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sps_buf ;
typedef  int /*<<< orphan*/  pps_buf ;
struct TYPE_34__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_36__ {int VPSBufSize; int /*<<< orphan*/ * VPSBuffer; TYPE_5__ Header; } ;
typedef  TYPE_7__ mfxExtCodingOptionVPS ;
struct TYPE_29__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_37__ {int SPSBufSize; int PPSBufSize; int /*<<< orphan*/ * PPSBuffer; int /*<<< orphan*/ * SPSBuffer; TYPE_1__ Header; } ;
typedef  TYPE_8__ mfxExtCodingOptionSPSPPS ;
struct TYPE_33__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_38__ {TYPE_4__ Header; } ;
typedef  TYPE_9__ mfxExtCodingOption3 ;
struct TYPE_32__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_24__ {TYPE_3__ Header; } ;
typedef  TYPE_10__ mfxExtCodingOption2 ;
struct TYPE_31__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_25__ {TYPE_2__ Header; } ;
typedef  TYPE_11__ mfxExtCodingOption ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
typedef  int /*<<< orphan*/  extradata_vps ;
typedef  int /*<<< orphan*/  extradata ;
typedef  int /*<<< orphan*/  co3 ;
typedef  int /*<<< orphan*/  co2 ;
typedef  int /*<<< orphan*/  co ;
struct TYPE_35__ {int BufferSizeInKB; int BRCParamMultiplier; } ;
struct TYPE_30__ {int NumExtParam; TYPE_6__ mfx; int /*<<< orphan*/ ** ExtParam; } ;
struct TYPE_28__ {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  avg_bitrate; int /*<<< orphan*/  min_bitrate; int /*<<< orphan*/  max_bitrate; } ;
struct TYPE_27__ {scalar_t__ codec_id; int extradata_size; int extradata; int /*<<< orphan*/  rc_buffer_size; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  rc_min_rate; int /*<<< orphan*/  rc_max_rate; } ;
struct TYPE_26__ {int hevc_vps; int packet_size; TYPE_23__ param; int /*<<< orphan*/  session; int /*<<< orphan*/  ver; } ;
typedef  TYPE_12__ QSVEncContext ;
typedef  TYPE_13__ AVCodecContext ;
typedef  TYPE_14__ AVCPBProperties ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MFXVideoENCODE_GetVideoParam (int /*<<< orphan*/ ,TYPE_23__*) ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION2 ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION3 ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION_SPSPPS ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION_VPS ; 
 int /*<<< orphan*/  QSV_HAVE_CO2 ; 
 int QSV_HAVE_CO3 ; 
 int QSV_HAVE_CO_VPS ; 
 scalar_t__ QSV_RUNTIME_VERSION_ATLEAST (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 int av_malloc (int) ; 
 int /*<<< orphan*/  dump_video_param (TYPE_13__*,TYPE_12__*,int /*<<< orphan*/ **) ; 
 TYPE_14__* ff_add_cpb_side_data (TYPE_13__*) ; 
 int ff_qsv_print_error (TYPE_13__*,int,char*) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qsv_retrieve_enc_params(AVCodecContext *avctx, QSVEncContext *q)
{
    AVCPBProperties *cpb_props;

    uint8_t sps_buf[128];
    uint8_t pps_buf[128];

    mfxExtCodingOptionSPSPPS extradata = {
        .Header.BufferId = MFX_EXTBUFF_CODING_OPTION_SPSPPS,
        .Header.BufferSz = sizeof(extradata),
        .SPSBuffer = sps_buf, .SPSBufSize = sizeof(sps_buf),
        .PPSBuffer = pps_buf, .PPSBufSize = sizeof(pps_buf)
    };

    mfxExtCodingOption co = {
        .Header.BufferId = MFX_EXTBUFF_CODING_OPTION,
        .Header.BufferSz = sizeof(co),
    };
#if QSV_HAVE_CO2
    mfxExtCodingOption2 co2 = {
        .Header.BufferId = MFX_EXTBUFF_CODING_OPTION2,
        .Header.BufferSz = sizeof(co2),
    };
#endif
#if QSV_HAVE_CO3
    mfxExtCodingOption3 co3 = {
        .Header.BufferId = MFX_EXTBUFF_CODING_OPTION3,
        .Header.BufferSz = sizeof(co3),
    };
#endif

#if QSV_HAVE_CO_VPS
    uint8_t vps_buf[128];
    mfxExtCodingOptionVPS extradata_vps = {
        .Header.BufferId = MFX_EXTBUFF_CODING_OPTION_VPS,
        .Header.BufferSz = sizeof(extradata_vps),
        .VPSBuffer       = vps_buf,
        .VPSBufSize      = sizeof(vps_buf),
    };
#endif

    mfxExtBuffer *ext_buffers[2 + QSV_HAVE_CO2 + QSV_HAVE_CO3 + QSV_HAVE_CO_VPS];

    int need_pps = avctx->codec_id != AV_CODEC_ID_MPEG2VIDEO;
    int ret, ext_buf_num = 0, extradata_offset = 0;

    ext_buffers[ext_buf_num++] = (mfxExtBuffer*)&extradata;
    ext_buffers[ext_buf_num++] = (mfxExtBuffer*)&co;
#if QSV_HAVE_CO2
    ext_buffers[ext_buf_num++] = (mfxExtBuffer*)&co2;
#endif
#if QSV_HAVE_CO3
    ext_buffers[ext_buf_num++] = (mfxExtBuffer*)&co3;
#endif
#if QSV_HAVE_CO_VPS
    q->hevc_vps = ((avctx->codec_id == AV_CODEC_ID_HEVC) && QSV_RUNTIME_VERSION_ATLEAST(q->ver, 1, 17));
    if (q->hevc_vps)
        ext_buffers[ext_buf_num++] = (mfxExtBuffer*)&extradata_vps;
#endif

    q->param.ExtParam    = ext_buffers;
    q->param.NumExtParam = ext_buf_num;

    ret = MFXVideoENCODE_GetVideoParam(q->session, &q->param);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error calling GetVideoParam");

    q->packet_size = q->param.mfx.BufferSizeInKB * q->param.mfx.BRCParamMultiplier * 1000;

    if (!extradata.SPSBufSize || (need_pps && !extradata.PPSBufSize)
#if QSV_HAVE_CO_VPS
        || (q->hevc_vps && !extradata_vps.VPSBufSize)
#endif
    ) {
        av_log(avctx, AV_LOG_ERROR, "No extradata returned from libmfx.\n");
        return AVERROR_UNKNOWN;
    }

    avctx->extradata_size = extradata.SPSBufSize + need_pps * extradata.PPSBufSize;
#if QSV_HAVE_CO_VPS
    avctx->extradata_size += q->hevc_vps * extradata_vps.VPSBufSize;
#endif

    avctx->extradata = av_malloc(avctx->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!avctx->extradata)
        return AVERROR(ENOMEM);

#if QSV_HAVE_CO_VPS
    if (q->hevc_vps) {
        memcpy(avctx->extradata, vps_buf, extradata_vps.VPSBufSize);
        extradata_offset += extradata_vps.VPSBufSize;
    }
#endif

    memcpy(avctx->extradata + extradata_offset, sps_buf, extradata.SPSBufSize);
    extradata_offset += extradata.SPSBufSize;
    if (need_pps) {
        memcpy(avctx->extradata + extradata_offset, pps_buf, extradata.PPSBufSize);
        extradata_offset += extradata.PPSBufSize;
    }
    memset(avctx->extradata + avctx->extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    cpb_props = ff_add_cpb_side_data(avctx);
    if (!cpb_props)
        return AVERROR(ENOMEM);
    cpb_props->max_bitrate = avctx->rc_max_rate;
    cpb_props->min_bitrate = avctx->rc_min_rate;
    cpb_props->avg_bitrate = avctx->bit_rate;
    cpb_props->buffer_size = avctx->rc_buffer_size;

    dump_video_param(avctx, q, ext_buffers + 1);

    return 0;
}