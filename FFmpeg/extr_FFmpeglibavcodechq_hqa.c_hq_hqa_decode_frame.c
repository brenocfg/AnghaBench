#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_22__ {TYPE_1__* priv_data; } ;
struct TYPE_21__ {int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_20__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_19__ {TYPE_12__ gbc; } ;
typedef  TYPE_1__ HQContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 unsigned int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_bytes_left (TYPE_12__*) ; 
 void* bytestream2_get_le32 (TYPE_12__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_12__*,int /*<<< orphan*/ ,int) ; 
 unsigned int bytestream2_peek_le32 (TYPE_12__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_12__*,int) ; 
 int /*<<< orphan*/  ff_canopus_parse_info_tag (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int hq_decode_frame (TYPE_1__*,TYPE_3__*,unsigned int,unsigned int) ; 
 int hqa_decode_frame (TYPE_1__*,TYPE_3__*,unsigned int) ; 

__attribute__((used)) static int hq_hqa_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame, AVPacket *avpkt)
{
    HQContext *ctx = avctx->priv_data;
    AVFrame *pic = data;
    uint32_t info_tag;
    unsigned int data_size;
    int ret;
    unsigned tag;

    bytestream2_init(&ctx->gbc, avpkt->data, avpkt->size);
    if (bytestream2_get_bytes_left(&ctx->gbc) < 4 + 4) {
        av_log(avctx, AV_LOG_ERROR, "Frame is too small (%d).\n", avpkt->size);
        return AVERROR_INVALIDDATA;
    }

    info_tag = bytestream2_peek_le32(&ctx->gbc);
    if (info_tag == MKTAG('I', 'N', 'F', 'O')) {
        int info_size;
        bytestream2_skip(&ctx->gbc, 4);
        info_size = bytestream2_get_le32(&ctx->gbc);
        if (bytestream2_get_bytes_left(&ctx->gbc) < info_size) {
            av_log(avctx, AV_LOG_ERROR, "Invalid INFO size (%d).\n", info_size);
            return AVERROR_INVALIDDATA;
        }
        ff_canopus_parse_info_tag(avctx, ctx->gbc.buffer, info_size);

        bytestream2_skip(&ctx->gbc, info_size);
    }

    data_size = bytestream2_get_bytes_left(&ctx->gbc);
    if (data_size < 4) {
        av_log(avctx, AV_LOG_ERROR, "Frame is too small (%d).\n", data_size);
        return AVERROR_INVALIDDATA;
    }

    /* HQ defines dimensions and number of slices, and thus slice traversal
     * order. HQA has no size constraint and a fixed number of slices, so it
     * needs a separate scheme for it. */
    tag = bytestream2_get_le32(&ctx->gbc);
    if ((tag & 0x00FFFFFF) == (MKTAG('U', 'V', 'C', ' ') & 0x00FFFFFF)) {
        ret = hq_decode_frame(ctx, pic, tag >> 24, data_size);
    } else if (tag == MKTAG('H', 'Q', 'A', '1')) {
        ret = hqa_decode_frame(ctx, pic, data_size);
    } else {
        av_log(avctx, AV_LOG_ERROR, "Not a HQ/HQA frame.\n");
        return AVERROR_INVALIDDATA;
    }
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error decoding frame.\n");
        return ret;
    }

    pic->key_frame = 1;
    pic->pict_type = AV_PICTURE_TYPE_I;

    *got_frame = 1;

    return avpkt->size;
}