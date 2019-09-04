#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_19__ {int debug; int height; int width; int flags2; TYPE_1__* priv_data; } ;
struct TYPE_18__ {int** data; int palette_has_changed; int* linesize; int key_frame; void* pict_type; } ;
struct TYPE_17__ {int size; scalar_t__ data; } ;
struct TYPE_16__ {int* pal; int* decomp_buf; unsigned long dsize; TYPE_12__* prev; } ;
struct TYPE_15__ {int** data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ DxaDecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_UNKNOWN ; 
 int AVPALETTE_SIZE ; 
 int AV_CODEC_FLAG2_SHOW_ALL ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void* AV_PICTURE_TYPE_I ; 
 void* AV_PICTURE_TYPE_P ; 
 int DECOMP_BUF_PADDING ; 
 int FF_DEBUG_PICT_INFO ; 
 scalar_t__ MKTAG (char,unsigned char,char,char) ; 
 scalar_t__ Z_OK ; 
 int av_frame_ref (TYPE_12__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_12__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_be24 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ bytestream2_peek_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_13 (TYPE_4__*,TYPE_1__* const,int*,int,int*,unsigned long,int*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uncompress (int*,unsigned long*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
    AVFrame *frame = data;
    DxaDecContext * const c = avctx->priv_data;
    uint8_t *outptr, *srcptr, *tmpptr;
    unsigned long dsize;
    int i, j, compr, ret;
    int stride;
    int pc = 0;
    GetByteContext gb;

    bytestream2_init(&gb, avpkt->data, avpkt->size);

    /* make the palette available on the way out */
    if (bytestream2_peek_le32(&gb) == MKTAG('C','M','A','P')) {
        bytestream2_skip(&gb, 4);
        for(i = 0; i < 256; i++){
            c->pal[i] = 0xFFU << 24 | bytestream2_get_be24(&gb);
        }
        pc = 1;
    }

    if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;
    memcpy(frame->data[1], c->pal, AVPALETTE_SIZE);
    frame->palette_has_changed = pc;

    outptr = frame->data[0];
    srcptr = c->decomp_buf;
    tmpptr = c->prev->data[0];
    stride = frame->linesize[0];

    if (bytestream2_get_le32(&gb) == MKTAG('N','U','L','L'))
        compr = -1;
    else
        compr = bytestream2_get_byte(&gb);

    dsize = c->dsize;
    if (compr != 4 && compr != -1) {
        bytestream2_skip(&gb, 4);
        if (uncompress(c->decomp_buf, &dsize, avpkt->data + bytestream2_tell(&gb),
                       bytestream2_get_bytes_left(&gb)) != Z_OK) {
            av_log(avctx, AV_LOG_ERROR, "Uncompress failed!\n");
            return AVERROR_UNKNOWN;
        }
        memset(c->decomp_buf + dsize, 0, DECOMP_BUF_PADDING);
    }

    if (avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(avctx, AV_LOG_DEBUG, "compr:%2d, dsize:%d\n", compr, (int)dsize);

    switch(compr){
    case -1:
        frame->key_frame = 0;
        frame->pict_type = AV_PICTURE_TYPE_P;
        if (c->prev->data[0])
            memcpy(frame->data[0], c->prev->data[0], frame->linesize[0] * avctx->height);
        else{ // Should happen only when first frame is 'NULL'
            memset(frame->data[0], 0, frame->linesize[0] * avctx->height);
            frame->key_frame = 1;
            frame->pict_type = AV_PICTURE_TYPE_I;
        }
        break;
    case 2:
    case 4:
        frame->key_frame = 1;
        frame->pict_type = AV_PICTURE_TYPE_I;
        for (j = 0; j < avctx->height; j++) {
                memcpy(outptr, srcptr, avctx->width);
            outptr += stride;
            srcptr += avctx->width;
        }
        break;
    case 3:
    case 5:
        if (!tmpptr) {
            av_log(avctx, AV_LOG_ERROR, "Missing reference frame.\n");
            if (!(avctx->flags2 & AV_CODEC_FLAG2_SHOW_ALL))
                return AVERROR_INVALIDDATA;
        }
        frame->key_frame = 0;
        frame->pict_type = AV_PICTURE_TYPE_P;
        for (j = 0; j < avctx->height; j++) {
            if(tmpptr){
                for(i = 0; i < avctx->width; i++)
                    outptr[i] = srcptr[i] ^ tmpptr[i];
                tmpptr += stride;
            }else
                memcpy(outptr, srcptr, avctx->width);
            outptr += stride;
            srcptr += avctx->width;
        }
        break;
    case 12: // ScummVM coding
    case 13:
        frame->key_frame = 0;
        frame->pict_type = AV_PICTURE_TYPE_P;
        if (!c->prev->data[0]) {
            av_log(avctx, AV_LOG_ERROR, "Missing reference frame\n");
            return AVERROR_INVALIDDATA;
        }
        decode_13(avctx, c, frame->data[0], frame->linesize[0], srcptr, dsize, c->prev->data[0]);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown/unsupported compression type %d\n", compr);
        return AVERROR_INVALIDDATA;
    }

    av_frame_unref(c->prev);
    if ((ret = av_frame_ref(c->prev, frame)) < 0)
        return ret;

    *got_frame = 1;

    /* always report that the buffer was completely consumed */
    return avpkt->size;
}