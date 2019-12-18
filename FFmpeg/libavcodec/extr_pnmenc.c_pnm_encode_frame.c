#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int pix_fmt; int width; int height; } ;
struct TYPE_15__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int depth; } ;
struct TYPE_12__ {TYPE_1__* comp; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GRAY16BE 134 
#define  AV_PIX_FMT_GRAY8 133 
#define  AV_PIX_FMT_MONOWHITE 132 
#define  AV_PIX_FMT_RGB24 131 
#define  AV_PIX_FMT_RGB48BE 130 
#define  AV_PIX_FMT_YUV420P 129 
#define  AV_PIX_FMT_YUV420P16BE 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_image_get_buffer_size (int,int,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_10__* av_pix_fmt_desc_get (int const) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int,...) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pnm_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *p, int *got_packet)
{
    uint8_t *bytestream, *bytestream_start, *bytestream_end;
    int i, h, h1, c, n, linesize, ret;
    uint8_t *ptr, *ptr1, *ptr2;
    int size = av_image_get_buffer_size(avctx->pix_fmt,
                                        avctx->width, avctx->height, 1);

    if ((ret = ff_alloc_packet2(avctx, pkt, size + 200, 0)) < 0)
        return ret;

    bytestream_start =
    bytestream       = pkt->data;
    bytestream_end   = pkt->data + pkt->size;

    h  = avctx->height;
    h1 = h;
    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_MONOWHITE:
        c  = '4';
        n  = (avctx->width + 7) >> 3;
        break;
    case AV_PIX_FMT_GRAY8:
        c  = '5';
        n  = avctx->width;
        break;
    case AV_PIX_FMT_GRAY16BE:
        c  = '5';
        n  = avctx->width * 2;
        break;
    case AV_PIX_FMT_RGB24:
        c  = '6';
        n  = avctx->width * 3;
        break;
    case AV_PIX_FMT_RGB48BE:
        c  = '6';
        n  = avctx->width * 6;
        break;
    case AV_PIX_FMT_YUV420P:
        if (avctx->width & 1 || avctx->height & 1) {
            av_log(avctx, AV_LOG_ERROR, "pgmyuv needs even width and height\n");
            return AVERROR(EINVAL);
        }
        c  = '5';
        n  = avctx->width;
        h1 = (h * 3) / 2;
        break;
    case AV_PIX_FMT_YUV420P16BE:
        c  = '5';
        n  = avctx->width * 2;
        h1 = (h * 3) / 2;
        break;
    default:
        return -1;
    }
    snprintf(bytestream, bytestream_end - bytestream,
             "P%c\n%d %d\n", c, avctx->width, h1);
    bytestream += strlen(bytestream);
    if (avctx->pix_fmt != AV_PIX_FMT_MONOWHITE) {
        int maxdepth = (1 << av_pix_fmt_desc_get(avctx->pix_fmt)->comp[0].depth) - 1;
        snprintf(bytestream, bytestream_end - bytestream,
                 "%d\n", maxdepth);
        bytestream += strlen(bytestream);
    }

    ptr      = p->data[0];
    linesize = p->linesize[0];
    for (i = 0; i < h; i++) {
        memcpy(bytestream, ptr, n);
        bytestream += n;
        ptr        += linesize;
    }

    if (avctx->pix_fmt == AV_PIX_FMT_YUV420P || avctx->pix_fmt == AV_PIX_FMT_YUV420P16BE) {
        h >>= 1;
        n >>= 1;
        ptr1 = p->data[1];
        ptr2 = p->data[2];
        for (i = 0; i < h; i++) {
            memcpy(bytestream, ptr1, n);
            bytestream += n;
            memcpy(bytestream, ptr2, n);
            bytestream += n;
                ptr1 += p->linesize[1];
                ptr2 += p->linesize[2];
        }
    }
    pkt->size   = bytestream - bytestream_start;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}