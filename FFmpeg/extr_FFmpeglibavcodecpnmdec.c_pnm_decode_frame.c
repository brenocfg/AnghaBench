#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int pix_fmt; int width; int height; scalar_t__ bits_per_raw_sample; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int key_frame; unsigned char** data; int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_13__ {char* data; int size; } ;
struct TYPE_12__ {char* bytestream_start; char* bytestream; char* bytestream_end; int maxval; int type; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ PNMContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
#define  AV_PIX_FMT_GRAY16 141 
#define  AV_PIX_FMT_GRAY8 140 
#define  AV_PIX_FMT_GRAY8A 139 
#define  AV_PIX_FMT_MONOBLACK 138 
#define  AV_PIX_FMT_MONOWHITE 137 
#define  AV_PIX_FMT_RGB24 136 
#define  AV_PIX_FMT_RGB48 135 
#define  AV_PIX_FMT_RGBA 134 
#define  AV_PIX_FMT_RGBA64 133 
#define  AV_PIX_FMT_YA16 132 
#define  AV_PIX_FMT_YUV420P 131 
#define  AV_PIX_FMT_YUV420P10 130 
#define  AV_PIX_FMT_YUV420P16 129 
#define  AV_PIX_FMT_YUV420P9 128 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int av_be2ne16 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ av_log2 (int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int ff_pnm_decode_header (TYPE_4__*,TYPE_1__* const) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  samplecpy (unsigned char*,char*,int,int) ; 

__attribute__((used)) static int pnm_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf   = avpkt->data;
    int buf_size         = avpkt->size;
    PNMContext * const s = avctx->priv_data;
    AVFrame * const p    = data;
    int i, j, k, n, linesize, h, upgrade = 0, is_mono = 0;
    unsigned char *ptr;
    int components, sample_len, ret;

    s->bytestream_start =
    s->bytestream       = (uint8_t *)buf;
    s->bytestream_end   = (uint8_t *)buf + buf_size;

    if ((ret = ff_pnm_decode_header(avctx, s)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;
    p->pict_type = AV_PICTURE_TYPE_I;
    p->key_frame = 1;
    avctx->bits_per_raw_sample = av_log2(s->maxval) + 1;

    switch (avctx->pix_fmt) {
    default:
        return AVERROR(EINVAL);
    case AV_PIX_FMT_RGBA64:
        n = avctx->width * 8;
        components=4;
        sample_len=16;
        if (s->maxval < 65535)
            upgrade = 2;
        goto do_read;
    case AV_PIX_FMT_RGB48:
        n = avctx->width * 6;
        components=3;
        sample_len=16;
        if (s->maxval < 65535)
            upgrade = 2;
        goto do_read;
    case AV_PIX_FMT_RGBA:
        n = avctx->width * 4;
        components=4;
        sample_len=8;
        goto do_read;
    case AV_PIX_FMT_RGB24:
        n = avctx->width * 3;
        components=3;
        sample_len=8;
        if (s->maxval < 255)
            upgrade = 1;
        goto do_read;
    case AV_PIX_FMT_GRAY8:
        n = avctx->width;
        components=1;
        sample_len=8;
        if (s->maxval < 255)
            upgrade = 1;
        goto do_read;
    case AV_PIX_FMT_GRAY8A:
        n = avctx->width * 2;
        components=2;
        sample_len=8;
        goto do_read;
    case AV_PIX_FMT_GRAY16:
        n = avctx->width * 2;
        components=1;
        sample_len=16;
        if (s->maxval < 65535)
            upgrade = 2;
        goto do_read;
    case AV_PIX_FMT_YA16:
        n =  avctx->width * 4;
        components=2;
        sample_len=16;
        if (s->maxval < 65535)
            upgrade = 2;
        goto do_read;
    case AV_PIX_FMT_MONOWHITE:
    case AV_PIX_FMT_MONOBLACK:
        n = (avctx->width + 7) >> 3;
        components=1;
        sample_len=1;
        is_mono = 1;
    do_read:
        ptr      = p->data[0];
        linesize = p->linesize[0];
        if (n * avctx->height > s->bytestream_end - s->bytestream)
            return AVERROR_INVALIDDATA;
        if(s->type < 4 || (is_mono && s->type==7)){
            for (i=0; i<avctx->height; i++) {
                PutBitContext pb;
                init_put_bits(&pb, ptr, linesize);
                for(j=0; j<avctx->width * components; j++){
                    unsigned int c=0;
                    int v=0;
                    if(s->type < 4)
                    while(s->bytestream < s->bytestream_end && (*s->bytestream < '0' || *s->bytestream > '9' ))
                        s->bytestream++;
                    if(s->bytestream >= s->bytestream_end)
                        return AVERROR_INVALIDDATA;
                    if (is_mono) {
                        /* read a single digit */
                        v = (*s->bytestream++)&1;
                    } else {
                        /* read a sequence of digits */
                        for (k = 0; k < 5 && c <= 9; k += 1) {
                            v = 10*v + c;
                            c = (*s->bytestream++) - '0';
                        }
                        if (v > s->maxval) {
                            av_log(avctx, AV_LOG_ERROR, "value %d larger than maxval %d\n", v, s->maxval);
                            return AVERROR_INVALIDDATA;
                        }
                    }
                    if (sample_len == 16) {
                        ((uint16_t*)ptr)[j] = (((1<<sample_len)-1)*v + (s->maxval>>1))/s->maxval;
                    } else
                        put_bits(&pb, sample_len, (((1<<sample_len)-1)*v + (s->maxval>>1))/s->maxval);
                }
                if (sample_len != 16)
                    flush_put_bits(&pb);
                ptr+= linesize;
            }
        }else{
        for (i = 0; i < avctx->height; i++) {
            if (!upgrade)
                samplecpy(ptr, s->bytestream, n, s->maxval);
            else if (upgrade == 1) {
                unsigned int j, f = (255 * 128 + s->maxval / 2) / s->maxval;
                for (j = 0; j < n; j++)
                    ptr[j] = (s->bytestream[j] * f + 64) >> 7;
            } else if (upgrade == 2) {
                unsigned int j, v, f = (65535 * 32768 + s->maxval / 2) / s->maxval;
                for (j = 0; j < n / 2; j++) {
                    v = av_be2ne16(((uint16_t *)s->bytestream)[j]);
                    ((uint16_t *)ptr)[j] = (v * f + 16384) >> 15;
                }
            }
            s->bytestream += n;
            ptr           += linesize;
        }
        }
        break;
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV420P10:
        {
            unsigned char *ptr1, *ptr2;

            n        = avctx->width;
            ptr      = p->data[0];
            linesize = p->linesize[0];
            if (s->maxval >= 256)
                n *= 2;
            if (n * avctx->height * 3 / 2 > s->bytestream_end - s->bytestream)
                return AVERROR_INVALIDDATA;
            for (i = 0; i < avctx->height; i++) {
                samplecpy(ptr, s->bytestream, n, s->maxval);
                s->bytestream += n;
                ptr           += linesize;
            }
            ptr1 = p->data[1];
            ptr2 = p->data[2];
            n >>= 1;
            h = avctx->height >> 1;
            for (i = 0; i < h; i++) {
                samplecpy(ptr1, s->bytestream, n, s->maxval);
                s->bytestream += n;
                samplecpy(ptr2, s->bytestream, n, s->maxval);
                s->bytestream += n;
                ptr1 += p->linesize[1];
                ptr2 += p->linesize[2];
            }
        }
        break;
    case AV_PIX_FMT_YUV420P16:
        {
            uint16_t *ptr1, *ptr2;
            const int f = (65535 * 32768 + s->maxval / 2) / s->maxval;
            unsigned int j, v;

            n        = avctx->width * 2;
            ptr      = p->data[0];
            linesize = p->linesize[0];
            if (n * avctx->height * 3 / 2 > s->bytestream_end - s->bytestream)
                return AVERROR_INVALIDDATA;
            for (i = 0; i < avctx->height; i++) {
                for (j = 0; j < n / 2; j++) {
                    v = av_be2ne16(((uint16_t *)s->bytestream)[j]);
                    ((uint16_t *)ptr)[j] = (v * f + 16384) >> 15;
                }
                s->bytestream += n;
                ptr           += linesize;
            }
            ptr1 = (uint16_t*)p->data[1];
            ptr2 = (uint16_t*)p->data[2];
            n >>= 1;
            h = avctx->height >> 1;
            for (i = 0; i < h; i++) {
                for (j = 0; j < n / 2; j++) {
                    v = av_be2ne16(((uint16_t *)s->bytestream)[j]);
                    ptr1[j] = (v * f + 16384) >> 15;
                }
                s->bytestream += n;

                for (j = 0; j < n / 2; j++) {
                    v = av_be2ne16(((uint16_t *)s->bytestream)[j]);
                    ptr2[j] = (v * f + 16384) >> 15;
                }
                s->bytestream += n;

                ptr1 += p->linesize[1] / 2;
                ptr2 += p->linesize[2] / 2;
            }
        }
        break;
    }
    *got_frame = 1;

    return s->bytestream - s->bytestream_start;
}