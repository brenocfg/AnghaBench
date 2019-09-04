#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_21__ {int (* dxt1_block ) (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ;int (* dxt3_block ) (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TextureDSPContext ;
struct TYPE_25__ {int height; int width; void* coded_height; void* coded_width; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_24__ {unsigned int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_23__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_22__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ GetByteContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_CEIL_RSHIFT (unsigned int,int) ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGBA ; 
 void* FFALIGN (unsigned int,int) ; 
#define  TXD_DXT1 129 
#define  TXD_DXT3 128 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_5__*,char*,unsigned int) ; 
 unsigned int bytestream2_get_be32 (TYPE_2__*) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_get_byte (TYPE_2__*) ; 
 unsigned int bytestream2_get_bytes_left (TYPE_2__*) ; 
 unsigned int bytestream2_get_le16 (TYPE_2__*) ; 
 unsigned int bytestream2_get_le32 (TYPE_2__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_2__*,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__* const,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_5__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ff_texturedsp_init (TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txd_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt) {
    GetByteContext gb;
    TextureDSPContext dxtc;
    AVFrame * const p = data;
    unsigned int version, w, h, d3d_format, depth, stride, flags;
    unsigned int y, v;
    uint8_t *ptr;
    uint32_t *pal;
    int i, j;
    int ret;

    ff_texturedsp_init(&dxtc);

    bytestream2_init(&gb, avpkt->data, avpkt->size);
    version         = bytestream2_get_le32(&gb);
    bytestream2_skip(&gb, 72);
    d3d_format      = bytestream2_get_le32(&gb);
    w               = bytestream2_get_le16(&gb);
    h               = bytestream2_get_le16(&gb);
    depth           = bytestream2_get_byte(&gb);
    bytestream2_skip(&gb, 2);
    flags           = bytestream2_get_byte(&gb);

    if (version < 8 || version > 9) {
        avpriv_report_missing_feature(avctx, "Texture data version %u", version);
        return AVERROR_PATCHWELCOME;
    }

    if (depth == 8) {
        avctx->pix_fmt = AV_PIX_FMT_PAL8;
    } else if (depth == 16 || depth == 32) {
        avctx->pix_fmt = AV_PIX_FMT_RGBA;
    } else {
        avpriv_report_missing_feature(avctx, "Color depth of %u", depth);
        return AVERROR_PATCHWELCOME;
    }

    if ((ret = ff_set_dimensions(avctx, w, h)) < 0)
        return ret;

    avctx->coded_width  = FFALIGN(w, 4);
    avctx->coded_height = FFALIGN(h, 4);

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;

    p->pict_type = AV_PICTURE_TYPE_I;

    ptr    = p->data[0];
    stride = p->linesize[0];

    if (depth == 8) {
        pal = (uint32_t *) p->data[1];
        for (y = 0; y < 256; y++) {
            v = bytestream2_get_be32(&gb);
            pal[y] = (v >> 8) + (v << 24);
        }
        if (bytestream2_get_bytes_left(&gb) < w * h)
            return AVERROR_INVALIDDATA;
        bytestream2_skip(&gb, 4);
        for (y=0; y<h; y++) {
            bytestream2_get_buffer(&gb, ptr, w);
            ptr += stride;
        }
    } else if (depth == 16) {
        bytestream2_skip(&gb, 4);
        switch (d3d_format) {
        case 0:
            if (!(flags & 1))
                goto unsupported;
        case TXD_DXT1:
            if (bytestream2_get_bytes_left(&gb) < AV_CEIL_RSHIFT(w, 2) * AV_CEIL_RSHIFT(h, 2) * 8)
                return AVERROR_INVALIDDATA;
            for (j = 0; j < avctx->height; j += 4) {
                for (i = 0; i < avctx->width; i += 4) {
                    uint8_t *p = ptr + i * 4 + j * stride;
                    int step = dxtc.dxt1_block(p, stride, gb.buffer);
                    bytestream2_skip(&gb, step);
                }
            }
            break;
        case TXD_DXT3:
            if (bytestream2_get_bytes_left(&gb) < AV_CEIL_RSHIFT(w, 2) * AV_CEIL_RSHIFT(h, 2) * 16)
                return AVERROR_INVALIDDATA;
            for (j = 0; j < avctx->height; j += 4) {
                for (i = 0; i < avctx->width; i += 4) {
                    uint8_t *p = ptr + i * 4 + j * stride;
                    int step = dxtc.dxt3_block(p, stride, gb.buffer);
                    bytestream2_skip(&gb, step);
                }
            }
            break;
        default:
            goto unsupported;
        }
    } else if (depth == 32) {
        switch (d3d_format) {
        case 0x15:
        case 0x16:
            if (bytestream2_get_bytes_left(&gb) < h * w * 4)
                return AVERROR_INVALIDDATA;
            for (y=0; y<h; y++) {
                bytestream2_get_buffer(&gb, ptr, w * 4);
                ptr += stride;
            }
            break;
        default:
            goto unsupported;
        }
    }

    *got_frame = 1;

    return avpkt->size;

unsupported:
    avpriv_report_missing_feature(avctx, "d3d format (%08x)", d3d_format);
    return AVERROR_PATCHWELCOME;
}