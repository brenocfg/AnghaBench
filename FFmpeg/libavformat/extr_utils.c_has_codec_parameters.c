#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ codec_id; int codec_type; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  frame_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  num; } ;
struct TYPE_15__ {int /*<<< orphan*/  codec_info_nb_frames; TYPE_5__* codecpar; TYPE_3__ sample_aspect_ratio; TYPE_2__* info; int /*<<< orphan*/  nb_decoded_frames; TYPE_1__* internal; } ;
struct TYPE_13__ {int /*<<< orphan*/  num; } ;
struct TYPE_14__ {TYPE_4__ sample_aspect_ratio; int /*<<< orphan*/  codec_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  found_decoder; } ;
struct TYPE_10__ {TYPE_7__* avctx; } ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 131 
#define  AVMEDIA_TYPE_DATA 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 scalar_t__ AV_CODEC_ID_DTS ; 
 scalar_t__ AV_CODEC_ID_HDMV_PGS_SUBTITLE ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_CODEC_ID_RV30 ; 
 int /*<<< orphan*/  AV_CODEC_ID_RV40 ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_NONE ; 
 int /*<<< orphan*/  FAIL (char*) ; 
 int /*<<< orphan*/  determinable_frame_size (TYPE_7__*) ; 

__attribute__((used)) static int has_codec_parameters(AVStream *st, const char **errmsg_ptr)
{
    AVCodecContext *avctx = st->internal->avctx;

#define FAIL(errmsg) do {                                         \
        if (errmsg_ptr)                                           \
            *errmsg_ptr = errmsg;                                 \
        return 0;                                                 \
    } while (0)

    if (   avctx->codec_id == AV_CODEC_ID_NONE
        && avctx->codec_type != AVMEDIA_TYPE_DATA)
        FAIL("unknown codec");
    switch (avctx->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        if (!avctx->frame_size && determinable_frame_size(avctx))
            FAIL("unspecified frame size");
        if (st->info->found_decoder >= 0 &&
            avctx->sample_fmt == AV_SAMPLE_FMT_NONE)
            FAIL("unspecified sample format");
        if (!avctx->sample_rate)
            FAIL("unspecified sample rate");
        if (!avctx->channels)
            FAIL("unspecified number of channels");
        if (st->info->found_decoder >= 0 && !st->nb_decoded_frames && avctx->codec_id == AV_CODEC_ID_DTS)
            FAIL("no decodable DTS frames");
        break;
    case AVMEDIA_TYPE_VIDEO:
        if (!avctx->width)
            FAIL("unspecified size");
        if (st->info->found_decoder >= 0 && avctx->pix_fmt == AV_PIX_FMT_NONE)
            FAIL("unspecified pixel format");
        if (st->codecpar->codec_id == AV_CODEC_ID_RV30 || st->codecpar->codec_id == AV_CODEC_ID_RV40)
            if (!st->sample_aspect_ratio.num && !st->codecpar->sample_aspect_ratio.num && !st->codec_info_nb_frames)
                FAIL("no frame in rv30/40 and no sar");
        break;
    case AVMEDIA_TYPE_SUBTITLE:
        if (avctx->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE && !avctx->width)
            FAIL("unspecified size");
        break;
    case AVMEDIA_TYPE_DATA:
        if (avctx->codec_id == AV_CODEC_ID_NONE) return 1;
    }

    return 1;
}