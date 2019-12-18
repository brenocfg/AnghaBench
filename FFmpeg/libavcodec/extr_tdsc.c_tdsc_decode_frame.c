#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uLongf ;
struct TYPE_17__ {int width; scalar_t__ height; TYPE_1__* priv_data; } ;
struct TYPE_16__ {int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int width; scalar_t__ height; int deflatelen; int /*<<< orphan*/  refframe; int /*<<< orphan*/  gbc; int /*<<< orphan*/  deflatebuffer; } ;
typedef  TYPE_1__ TDSCContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int MKTAG (char,char,char,char) ; 
 int TDSF_HEADER_SIZE ; 
 int av_frame_copy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_reallocp (int /*<<< orphan*/ *,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdsc_paint_cursor (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tdsc_parse_dtsm (TYPE_4__*) ; 
 int tdsc_parse_tdsf (TYPE_4__*,int) ; 
 int uncompress (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tdsc_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    TDSCContext *ctx = avctx->priv_data;
    AVFrame *frame = data;
    int ret, tag_header, keyframe = 0;
    uLongf dlen;

    /* Resize deflate buffer on resolution change */
    if (ctx->width != avctx->width || ctx->height != avctx->height) {
        ctx->deflatelen = avctx->width * avctx->height * (3 + 1);
        ret = av_reallocp(&ctx->deflatebuffer, ctx->deflatelen);
        if (ret < 0)
            return ret;
    }
    dlen = ctx->deflatelen;

    /* Frames are deflated, need to inflate them first */
    ret = uncompress(ctx->deflatebuffer, &dlen, avpkt->data, avpkt->size);
    if (ret) {
        av_log(avctx, AV_LOG_ERROR, "Deflate error %d.\n", ret);
        return AVERROR_UNKNOWN;
    }

    bytestream2_init(&ctx->gbc, ctx->deflatebuffer, dlen);

    /* Check for tag and for size info */
    if (bytestream2_get_bytes_left(&ctx->gbc) < 4 + 4) {
        av_log(avctx, AV_LOG_ERROR, "Frame is too small.\n");
        return AVERROR_INVALIDDATA;
    }

    /* Read tag */
    tag_header = bytestream2_get_le32(&ctx->gbc);

    if (tag_header == MKTAG('T','D','S','F')) {
        int number_tiles;
        if (bytestream2_get_bytes_left(&ctx->gbc) < TDSF_HEADER_SIZE) {
            av_log(avctx, AV_LOG_ERROR, "TDSF tag is too small.\n");
            return AVERROR_INVALIDDATA;
        }
        /* First 4 bytes here are the number of GEPJ/WAR tiles in this frame */
        number_tiles = bytestream2_get_le32(&ctx->gbc);

        bytestream2_skip(&ctx->gbc, 4); // internal timestamp maybe?
        keyframe = bytestream2_get_le32(&ctx->gbc) == 0x30;

        ret = tdsc_parse_tdsf(avctx, number_tiles);
        if (ret < 0)
            return ret;

        /* Check if there is anything else we are able to parse */
        if (bytestream2_get_bytes_left(&ctx->gbc) >= 4 + 4)
            tag_header = bytestream2_get_le32(&ctx->gbc);
    }

    /* This tag can be after a TDSF block or on its own frame */
    if (tag_header == MKTAG('D','T','S','M')) {
        /* First 4 bytes here are the total size in bytes for this frame */
        int tag_size = bytestream2_get_le32(&ctx->gbc);

        if (bytestream2_get_bytes_left(&ctx->gbc) < tag_size) {
            av_log(avctx, AV_LOG_ERROR, "DTSM tag is too small.\n");
            return AVERROR_INVALIDDATA;
        }

        ret = tdsc_parse_dtsm(avctx);
        if (ret < 0)
            return ret;
    }

    /* Get the output frame and copy the reference frame */
    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0)
        return ret;

    ret = av_frame_copy(frame, ctx->refframe);
    if (ret < 0)
        return ret;

    /* Paint the cursor on the output frame */
    tdsc_paint_cursor(avctx, frame->data[0], frame->linesize[0]);

    /* Frame is ready to be output */
    if (keyframe) {
        frame->pict_type = AV_PICTURE_TYPE_I;
        frame->key_frame = 1;
    } else {
        frame->pict_type = AV_PICTURE_TYPE_P;
    }
    *got_frame = 1;

    return avpkt->size;
}