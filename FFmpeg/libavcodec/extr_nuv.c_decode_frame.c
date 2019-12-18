#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_19__ {char** data; int* linesize; int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_18__ {int height; int /*<<< orphan*/  frame_number; TYPE_1__* priv_data; } ;
struct TYPE_17__ {char* data; int size; } ;
struct TYPE_16__ {int width; int height; int decomp_size; char* decomp_buf; TYPE_6__* pic; int /*<<< orphan*/  rtj; scalar_t__ codec_frameheader; int /*<<< orphan*/  cq; int /*<<< orphan*/  lq; } ;
typedef  TYPE_1__ NuvContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LZO_OUTPUT_PADDING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int AV_RL16 (char const*) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FF_REGET_BUFFER_FLAG_READONLY ; 
 int RTJPEG_HEADER_SIZE ; 
 int av_frame_ref (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_lzo1x_decode (char*,int*,char const*,int*) ; 
 int codec_reinit (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  copy_frame (TYPE_6__*,char const*,int,int) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_6__*,int) ; 
 int ff_rtjpeg_decode_frame_yuv420 (int /*<<< orphan*/ *,TYPE_6__*,char const*,int) ; 
 int /*<<< orphan*/  ff_rtjpeg_decode_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_quant (TYPE_3__*,TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    NuvContext *c      = avctx->priv_data;
    AVFrame *picture   = data;
    int orig_size      = buf_size;
    int keyframe, ret;
    int size_change = 0;
    int minsize = 0;
    int flags = 0;
    int result, init_frame = !avctx->frame_number;
    enum {
        NUV_UNCOMPRESSED  = '0',
        NUV_RTJPEG        = '1',
        NUV_RTJPEG_IN_LZO = '2',
        NUV_LZO           = '3',
        NUV_BLACK         = 'N',
        NUV_COPY_LAST     = 'L'
    } comptype;

    if (buf_size < 12) {
        av_log(avctx, AV_LOG_ERROR, "coded frame too small\n");
        return AVERROR_INVALIDDATA;
    }

    // codec data (rtjpeg quant tables)
    if (buf[0] == 'D' && buf[1] == 'R') {
        int ret;
        // Skip the rest of the frame header.
        buf       = &buf[12];
        buf_size -= 12;
        ret       = get_quant(avctx, c, buf, buf_size);
        if (ret < 0)
            return ret;
        ff_rtjpeg_decode_init(&c->rtj, c->width, c->height, c->lq, c->cq);
        return orig_size;
    }

    if (buf_size < 12 || buf[0] != 'V') {
        av_log(avctx, AV_LOG_ERROR, "not a nuv video frame\n");
        return AVERROR_INVALIDDATA;
    }
    comptype = buf[1];
    switch (comptype) {
    case NUV_RTJPEG_IN_LZO:
    case NUV_RTJPEG:
        keyframe = !buf[2];
        if (c->width < 16 || c->height < 16) {
            return AVERROR_INVALIDDATA;
        }
        break;
    case NUV_COPY_LAST:
        flags |= FF_REGET_BUFFER_FLAG_READONLY;
        keyframe = 0;
        break;
    default:
        keyframe = 1;
        break;
    }
    switch (comptype) {
    case NUV_UNCOMPRESSED:
        minsize = c->width * c->height * 3 / 2;
        break;
    case NUV_RTJPEG:
        minsize = c->width/16 * (c->height/16) * 6;
        break;
    }
    if (buf_size < minsize / 4)
        return AVERROR_INVALIDDATA;
retry:
    // Skip the rest of the frame header.
    buf       = &buf[12];
    buf_size -= 12;
    if (comptype == NUV_RTJPEG_IN_LZO || comptype == NUV_LZO) {
        int outlen = c->decomp_size - FFMAX(AV_INPUT_BUFFER_PADDING_SIZE, AV_LZO_OUTPUT_PADDING);
        int inlen  = buf_size;
        if (av_lzo1x_decode(c->decomp_buf, &outlen, buf, &inlen)) {
            av_log(avctx, AV_LOG_ERROR, "error during lzo decompression\n");
            return AVERROR_INVALIDDATA;
        }
        buf      = c->decomp_buf;
        buf_size = c->decomp_size - FFMAX(AV_INPUT_BUFFER_PADDING_SIZE, AV_LZO_OUTPUT_PADDING) - outlen;
        memset(c->decomp_buf + buf_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    }
    if (c->codec_frameheader) {
        int w, h, q;
        if (buf_size < RTJPEG_HEADER_SIZE) {
            av_log(avctx, AV_LOG_ERROR, "Too small NUV video frame\n");
            return AVERROR_INVALIDDATA;
        }
        // There seem to exist two variants of this header: one starts with 'V'
        // and 5 bytes unknown, the other matches current MythTV and is 4 bytes size,
        // 1 byte header size (== 12), 1 byte version (== 0)
        if (buf[0] != 'V' && AV_RL16(&buf[4]) != 0x000c) {
            av_log(avctx, AV_LOG_ERROR, "Unknown secondary frame header (wrong codec_tag?)\n");
            return AVERROR_INVALIDDATA;
        }
        w = AV_RL16(&buf[6]);
        h = AV_RL16(&buf[8]);
        q = buf[10];
        if ((result = codec_reinit(avctx, w, h, q)) < 0)
            return result;
        if (result) {
            buf = avpkt->data;
            buf_size = avpkt->size;
            size_change = 1;
            goto retry;
        }
        buf       = &buf[RTJPEG_HEADER_SIZE];
        buf_size -= RTJPEG_HEADER_SIZE;
    }

    if (size_change || keyframe) {
        av_frame_unref(c->pic);
        init_frame = 1;
    }

    if ((result = ff_reget_buffer(avctx, c->pic, flags)) < 0)
        return result;
    if (init_frame) {
        memset(c->pic->data[0], 0,    avctx->height * c->pic->linesize[0]);
        memset(c->pic->data[1], 0x80, avctx->height * c->pic->linesize[1] / 2);
        memset(c->pic->data[2], 0x80, avctx->height * c->pic->linesize[2] / 2);
    }

    c->pic->pict_type = keyframe ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;
    c->pic->key_frame = keyframe;
    // decompress/copy/whatever data
    switch (comptype) {
    case NUV_LZO:
    case NUV_UNCOMPRESSED: {
        int height = c->height;
        if (buf_size < c->width * height * 3 / 2) {
            av_log(avctx, AV_LOG_ERROR, "uncompressed frame too short\n");
            height = buf_size / c->width / 3 * 2;
        }
        if(height > 0)
            copy_frame(c->pic, buf, c->width, height);
        break;
    }
    case NUV_RTJPEG_IN_LZO:
    case NUV_RTJPEG:
        ret = ff_rtjpeg_decode_frame_yuv420(&c->rtj, c->pic, buf, buf_size);
        if (ret < 0)
            return ret;
        break;
    case NUV_BLACK:
        memset(c->pic->data[0], 0, c->width * c->height);
        memset(c->pic->data[1], 128, c->width * c->height / 4);
        memset(c->pic->data[2], 128, c->width * c->height / 4);
        break;
    case NUV_COPY_LAST:
        /* nothing more to do here */
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "unknown compression\n");
        return AVERROR_INVALIDDATA;
    }

    if ((result = av_frame_ref(picture, c->pic)) < 0)
        return result;

    *got_frame = 1;
    return orig_size;
}