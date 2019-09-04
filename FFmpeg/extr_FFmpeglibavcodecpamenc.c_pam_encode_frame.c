#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int height; int width; int pix_fmt; } ;
struct TYPE_10__ {int** data; int* linesize; } ;
struct TYPE_9__ {int* data; int size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
#define  AV_PIX_FMT_GRAY16BE 136 
#define  AV_PIX_FMT_GRAY8 135 
#define  AV_PIX_FMT_GRAY8A 134 
#define  AV_PIX_FMT_MONOBLACK 133 
#define  AV_PIX_FMT_RGB24 132 
#define  AV_PIX_FMT_RGB48BE 131 
#define  AV_PIX_FMT_RGBA 130 
#define  AV_PIX_FMT_RGBA64BE 129 
#define  AV_PIX_FMT_YA16BE 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  snprintf (int*,int,char*,int,int,int,int,char const*) ; 
 int /*<<< orphan*/  strlen (int*) ; 

__attribute__((used)) static int pam_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *p, int *got_packet)
{
    uint8_t *bytestream_start, *bytestream, *bytestream_end;
    int i, h, w, n, linesize, depth, maxval, ret;
    const char *tuple_type;
    uint8_t *ptr;

    h = avctx->height;
    w = avctx->width;
    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_MONOBLACK:
        n          = w;
        depth      = 1;
        maxval     = 1;
        tuple_type = "BLACKANDWHITE";
        break;
    case AV_PIX_FMT_GRAY8:
        n          = w;
        depth      = 1;
        maxval     = 255;
        tuple_type = "GRAYSCALE";
        break;
    case AV_PIX_FMT_GRAY16BE:
        n          = w * 2;
        depth      = 1;
        maxval     = 0xFFFF;
        tuple_type = "GRAYSCALE";
        break;
    case AV_PIX_FMT_GRAY8A:
        n          = w * 2;
        depth      = 2;
        maxval     = 255;
        tuple_type = "GRAYSCALE_ALPHA";
        break;
    case AV_PIX_FMT_YA16BE:
        n          = w * 4;
        depth      = 2;
        maxval     = 0xFFFF;
        tuple_type = "GRAYSCALE_ALPHA";
        break;
    case AV_PIX_FMT_RGB24:
        n          = w * 3;
        depth      = 3;
        maxval     = 255;
        tuple_type = "RGB";
        break;
    case AV_PIX_FMT_RGBA:
        n          = w * 4;
        depth      = 4;
        maxval     = 255;
        tuple_type = "RGB_ALPHA";
        break;
    case AV_PIX_FMT_RGB48BE:
        n          = w * 6;
        depth      = 3;
        maxval     = 0xFFFF;
        tuple_type = "RGB";
        break;
    case AV_PIX_FMT_RGBA64BE:
        n          = w * 8;
        depth      = 4;
        maxval     = 0xFFFF;
        tuple_type = "RGB_ALPHA";
        break;
    default:
        return -1;
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, n*h + 200, 0)) < 0)
        return ret;

    bytestream_start =
    bytestream       = pkt->data;
    bytestream_end   = pkt->data + pkt->size;

    snprintf(bytestream, bytestream_end - bytestream,
             "P7\nWIDTH %d\nHEIGHT %d\nDEPTH %d\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
             w, h, depth, maxval, tuple_type);
    bytestream += strlen(bytestream);

    ptr      = p->data[0];
    linesize = p->linesize[0];

    if (avctx->pix_fmt == AV_PIX_FMT_MONOBLACK){
        int j;
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++)
                *bytestream++ = ptr[j >> 3] >> (7 - j & 7) & 1;
            ptr += linesize;
        }
    } else {
        for (i = 0; i < h; i++) {
            memcpy(bytestream, ptr, n);
            bytestream += n;
            ptr        += linesize;
        }
    }

    pkt->size   = bytestream - bytestream_start;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}