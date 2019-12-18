#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_20__ {int extradata_size; int err_recognition; int /*<<< orphan*/  const* extradata; int /*<<< orphan*/  codec_tag; TYPE_4__* priv_data; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {scalar_t__ low_delay; scalar_t__ codec_tag; int timecode_frame_start; int /*<<< orphan*/ * current_picture_ptr; int /*<<< orphan*/  parse_context; TYPE_2__* avctx; TYPE_1__* next_picture_ptr; } ;
struct TYPE_17__ {scalar_t__ mpeg_enc_ctx_allocated; int extradata_decoded; scalar_t__ slice_count; TYPE_3__ mpeg_enc_ctx; } ;
struct TYPE_15__ {int flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ Mpeg1Context ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CODEC_FLAG_TRUNCATED ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_FRAME_DATA_GOP_TIMECODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_RB32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ AV_RL32 (char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SEQ_END_CODE ; 
 TYPE_6__* av_frame_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avpriv_toupper4 (int /*<<< orphan*/ ) ; 
 int decode_chunks (TYPE_7__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 
 int ff_mpeg1_find_frame_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  vcr2_init_sequence (TYPE_7__*) ; 

__attribute__((used)) static int mpeg_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_output, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int ret;
    int buf_size = avpkt->size;
    Mpeg1Context *s = avctx->priv_data;
    AVFrame *picture = data;
    MpegEncContext *s2 = &s->mpeg_enc_ctx;

    if (buf_size == 0 || (buf_size == 4 && AV_RB32(buf) == SEQ_END_CODE)) {
        /* special case for last picture */
        if (s2->low_delay == 0 && s2->next_picture_ptr) {
            int ret = av_frame_ref(picture, s2->next_picture_ptr->f);
            if (ret < 0)
                return ret;

            s2->next_picture_ptr = NULL;

            *got_output = 1;
        }
        return buf_size;
    }

    if (s2->avctx->flags & AV_CODEC_FLAG_TRUNCATED) {
        int next = ff_mpeg1_find_frame_end(&s2->parse_context, buf,
                                           buf_size, NULL);

        if (ff_combine_frame(&s2->parse_context, next,
                             (const uint8_t **) &buf, &buf_size) < 0)
            return buf_size;
    }

    s2->codec_tag = avpriv_toupper4(avctx->codec_tag);
    if (s->mpeg_enc_ctx_allocated == 0 && (   s2->codec_tag == AV_RL32("VCR2")
                                           || s2->codec_tag == AV_RL32("BW10")
                                          ))
        vcr2_init_sequence(avctx);

    s->slice_count = 0;

    if (avctx->extradata && !s->extradata_decoded) {
        ret = decode_chunks(avctx, picture, got_output,
                            avctx->extradata, avctx->extradata_size);
        if (*got_output) {
            av_log(avctx, AV_LOG_ERROR, "picture in extradata\n");
            av_frame_unref(picture);
            *got_output = 0;
        }
        s->extradata_decoded = 1;
        if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE)) {
            s2->current_picture_ptr = NULL;
            return ret;
        }
    }

    ret = decode_chunks(avctx, picture, got_output, buf, buf_size);
    if (ret<0 || *got_output) {
        s2->current_picture_ptr = NULL;

        if (s2->timecode_frame_start != -1 && *got_output) {
            AVFrameSideData *tcside = av_frame_new_side_data(picture,
                                                             AV_FRAME_DATA_GOP_TIMECODE,
                                                             sizeof(int64_t));
            if (!tcside)
                return AVERROR(ENOMEM);
            memcpy(tcside->data, &s2->timecode_frame_start, sizeof(int64_t));

            s2->timecode_frame_start = -1;
        }
    }

    return ret;
}