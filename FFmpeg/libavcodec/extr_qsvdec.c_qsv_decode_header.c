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

/* Type definitions */
struct TYPE_17__ {int CodecId; } ;
struct TYPE_18__ {TYPE_1__ mfx; } ;
typedef  TYPE_2__ mfxVideoParam ;
struct TYPE_19__ {int /*<<< orphan*/  DataFlag; int /*<<< orphan*/  TimeStamp; scalar_t__ DataLength; scalar_t__ MaxLength; int /*<<< orphan*/  Data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ mfxBitstream ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_22__ {scalar_t__ field_order; int /*<<< orphan*/  codec_id; } ;
struct TYPE_21__ {int /*<<< orphan*/  pts; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  session; } ;
typedef  TYPE_4__ QSVContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  EAGAIN ; 
 int MFXVideoDECODE_DecodeHeader (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MFX_BITSTREAM_COMPLETE_FRAME ; 
 int MFX_ERR_MORE_DATA ; 
 int ff_qsv_codec_id_to_mfx (int /*<<< orphan*/ ) ; 
 int ff_qsv_print_error (TYPE_6__*,int,char*) ; 
 int qsv_decode_preinit (TYPE_6__*,TYPE_4__*,int,TYPE_2__*) ; 

__attribute__((used)) static int qsv_decode_header(AVCodecContext *avctx, QSVContext *q, AVPacket *avpkt, enum AVPixelFormat pix_fmt, mfxVideoParam *param)
{
    int ret;

    mfxBitstream bs = { 0 };

    if (avpkt->size) {
        bs.Data       = avpkt->data;
        bs.DataLength = avpkt->size;
        bs.MaxLength  = bs.DataLength;
        bs.TimeStamp  = avpkt->pts;
        if (avctx->field_order == AV_FIELD_PROGRESSIVE)
            bs.DataFlag   |= MFX_BITSTREAM_COMPLETE_FRAME;
    } else
        return AVERROR_INVALIDDATA;


    if(!q->session) {
        ret = qsv_decode_preinit(avctx, q, pix_fmt, param);
        if (ret < 0)
            return ret;
    }

    ret = ff_qsv_codec_id_to_mfx(avctx->codec_id);
    if (ret < 0)
        return ret;

    param->mfx.CodecId = ret;
    ret = MFXVideoDECODE_DecodeHeader(q->session, &bs, param);
    if (MFX_ERR_MORE_DATA == ret) {
       return AVERROR(EAGAIN);
    }
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                "Error decoding stream header");

    return 0;
}