#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuple_type ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {scalar_t__ pix_fmt; scalar_t__ codec_id; int width; int height; } ;
struct TYPE_10__ {char type; scalar_t__ bytestream; scalar_t__ bytestream_end; int maxval; } ;
typedef  TYPE_1__ PNMContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_PGMYUV ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 void* AV_PIX_FMT_GRAY16 ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_GRAY8A ; 
 scalar_t__ AV_PIX_FMT_MONOBLACK ; 
 scalar_t__ AV_PIX_FMT_MONOWHITE ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 void* AV_PIX_FMT_RGB48 ; 
 scalar_t__ AV_PIX_FMT_RGBA ; 
 scalar_t__ AV_PIX_FMT_RGBA64 ; 
 scalar_t__ AV_PIX_FMT_YA16 ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV420P10 ; 
 scalar_t__ AV_PIX_FMT_YUV420P16 ; 
 scalar_t__ AV_PIX_FMT_YUV420P9 ; 
 int UINT16_MAX ; 
 void* atoi (char*) ; 
 scalar_t__ av_image_check_size (int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_7__* av_pix_fmt_desc_get (scalar_t__) ; 
 int ff_set_dimensions (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pnm_get (TYPE_1__* const,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

int ff_pnm_decode_header(AVCodecContext *avctx, PNMContext * const s)
{
    char buf1[32], tuple_type[32];
    int h, w, depth, maxval;
    int ret;

    pnm_get(s, buf1, sizeof(buf1));
    if(buf1[0] != 'P')
        return AVERROR_INVALIDDATA;
    s->type= buf1[1]-'0';

    if (s->type==1 || s->type==4) {
        avctx->pix_fmt = AV_PIX_FMT_MONOWHITE;
    } else if (s->type==2 || s->type==5) {
        if (avctx->codec_id == AV_CODEC_ID_PGMYUV)
            avctx->pix_fmt = AV_PIX_FMT_YUV420P;
        else
            avctx->pix_fmt = AV_PIX_FMT_GRAY8;
    } else if (s->type==3 || s->type==6) {
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
    } else if (s->type==7) {
        w      = -1;
        h      = -1;
        maxval = -1;
        depth  = -1;
        tuple_type[0] = '\0';
        for (;;) {
            pnm_get(s, buf1, sizeof(buf1));
            if (!strcmp(buf1, "WIDTH")) {
                pnm_get(s, buf1, sizeof(buf1));
                w = strtol(buf1, NULL, 10);
            } else if (!strcmp(buf1, "HEIGHT")) {
                pnm_get(s, buf1, sizeof(buf1));
                h = strtol(buf1, NULL, 10);
            } else if (!strcmp(buf1, "DEPTH")) {
                pnm_get(s, buf1, sizeof(buf1));
                depth = strtol(buf1, NULL, 10);
            } else if (!strcmp(buf1, "MAXVAL")) {
                pnm_get(s, buf1, sizeof(buf1));
                maxval = strtol(buf1, NULL, 10);
            } else if (!strcmp(buf1, "TUPLTYPE") ||
                       /* libavcodec used to write invalid files */
                       !strcmp(buf1, "TUPLETYPE")) {
                pnm_get(s, tuple_type, sizeof(tuple_type));
            } else if (!strcmp(buf1, "ENDHDR")) {
                break;
            } else {
                return AVERROR_INVALIDDATA;
            }
        }
        /* check that all tags are present */
        if (w <= 0 || h <= 0 || maxval <= 0 || maxval > UINT16_MAX || depth <= 0 || tuple_type[0] == '\0' ||
            av_image_check_size(w, h, 0, avctx) || s->bytestream >= s->bytestream_end)
            return AVERROR_INVALIDDATA;

        ret = ff_set_dimensions(avctx, w, h);
        if (ret < 0)
            return ret;
        s->maxval     = maxval;
        if (depth == 1) {
            if (maxval == 1) {
                avctx->pix_fmt = AV_PIX_FMT_MONOBLACK;
            } else if (maxval < 256) {
                avctx->pix_fmt = AV_PIX_FMT_GRAY8;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            }
        } else if (depth == 2) {
            if (maxval < 256) {
                avctx->pix_fmt = AV_PIX_FMT_GRAY8A;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_YA16;
            }
        } else if (depth == 3) {
            if (maxval < 256) {
                avctx->pix_fmt = AV_PIX_FMT_RGB24;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_RGB48;
            }
        } else if (depth == 4) {
            if (maxval < 256) {
                avctx->pix_fmt = AV_PIX_FMT_RGBA;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_RGBA64;
            }
        } else {
            return AVERROR_INVALIDDATA;
        }
        return 0;
    } else {
        return AVERROR_INVALIDDATA;
    }
    pnm_get(s, buf1, sizeof(buf1));
    w = atoi(buf1);
    pnm_get(s, buf1, sizeof(buf1));
    h = atoi(buf1);
    if(w <= 0 || h <= 0 || av_image_check_size(w, h, 0, avctx) || s->bytestream >= s->bytestream_end)
        return AVERROR_INVALIDDATA;

    ret = ff_set_dimensions(avctx, w, h);
    if (ret < 0)
        return ret;

    if (avctx->pix_fmt != AV_PIX_FMT_MONOWHITE && avctx->pix_fmt != AV_PIX_FMT_MONOBLACK) {
        pnm_get(s, buf1, sizeof(buf1));
        s->maxval = atoi(buf1);
        if (s->maxval <= 0 || s->maxval > UINT16_MAX) {
            av_log(avctx, AV_LOG_ERROR, "Invalid maxval: %d\n", s->maxval);
            s->maxval = 255;
        }
        if (s->maxval >= 256) {
            if (avctx->pix_fmt == AV_PIX_FMT_GRAY8) {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            } else if (avctx->pix_fmt == AV_PIX_FMT_RGB24) {
                avctx->pix_fmt = AV_PIX_FMT_RGB48;
            } else if (avctx->pix_fmt == AV_PIX_FMT_YUV420P && s->maxval < 65536) {
                if (s->maxval < 512)
                    avctx->pix_fmt = AV_PIX_FMT_YUV420P9;
                else if (s->maxval < 1024)
                    avctx->pix_fmt = AV_PIX_FMT_YUV420P10;
                else
                    avctx->pix_fmt = AV_PIX_FMT_YUV420P16;
            } else {
                av_log(avctx, AV_LOG_ERROR, "Unsupported pixel format\n");
                avctx->pix_fmt = AV_PIX_FMT_NONE;
                return AVERROR_INVALIDDATA;
            }
        }
    }else
        s->maxval=1;
    /* more check if YUV420 */
    if (av_pix_fmt_desc_get(avctx->pix_fmt)->flags & AV_PIX_FMT_FLAG_PLANAR) {
        if ((avctx->width & 1) != 0)
            return AVERROR_INVALIDDATA;
        h = (avctx->height * 2);
        if ((h % 3) != 0)
            return AVERROR_INVALIDDATA;
        h /= 3;
        avctx->height = h;
    }
    return 0;
}