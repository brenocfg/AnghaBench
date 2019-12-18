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

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pal ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_16__ {int pix_fmt; int width; int height; } ;
struct TYPE_15__ {int key_frame; int** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_14__ {int* data; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
#define  AV_PIX_FMT_ABGR 148 
#define  AV_PIX_FMT_ARGB 147 
#define  AV_PIX_FMT_BGR24 146 
#define  AV_PIX_FMT_BGR4_BYTE 145 
#define  AV_PIX_FMT_BGR555BE 144 
#define  AV_PIX_FMT_BGR555LE 143 
#define  AV_PIX_FMT_BGR565BE 142 
#define  AV_PIX_FMT_BGR565LE 141 
#define  AV_PIX_FMT_BGR8 140 
#define  AV_PIX_FMT_BGRA 139 
 int AV_PIX_FMT_FLAG_BE ; 
#define  AV_PIX_FMT_GRAY8 138 
#define  AV_PIX_FMT_MONOWHITE 137 
#define  AV_PIX_FMT_PAL8 136 
#define  AV_PIX_FMT_RGB24 135 
#define  AV_PIX_FMT_RGB4_BYTE 134 
#define  AV_PIX_FMT_RGB555BE 133 
#define  AV_PIX_FMT_RGB555LE 132 
#define  AV_PIX_FMT_RGB565BE 131 
#define  AV_PIX_FMT_RGB565LE 130 
#define  AV_PIX_FMT_RGB8 129 
#define  AV_PIX_FMT_RGBA 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFALIGN (int,int) ; 
 int* WINDOW_NAME ; 
 int WINDOW_NAME_SIZE ; 
 int XWD_CMAP_SIZE ; 
 int XWD_HEADER_SIZE ; 
 int XWD_PSEUDO_COLOR ; 
 int XWD_STATIC_GRAY ; 
 int XWD_TRUE_COLOR ; 
 int XWD_VERSION ; 
 int XWD_Z_PIXMAP ; 
 int av_get_bits_per_pixel (TYPE_1__ const*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  avpriv_set_systematic_pal2 (int*,int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int**,int*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int**,int) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int xwd_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *pict, int *got_packet)
{
    enum AVPixelFormat pix_fmt = avctx->pix_fmt;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    uint32_t pixdepth, bpp, bpad, ncolors = 0, lsize, vclass, be = 0;
    uint32_t rgb[3] = { 0 }, bitorder = 0;
    uint32_t header_size;
    int i, out_size, ret;
    uint8_t *ptr, *buf;
    AVFrame * const p = (AVFrame *)pict;
    uint32_t pal[256];

    pixdepth = av_get_bits_per_pixel(desc);
    if (desc->flags & AV_PIX_FMT_FLAG_BE)
        be = 1;
    switch (pix_fmt) {
    case AV_PIX_FMT_ARGB:
    case AV_PIX_FMT_BGRA:
    case AV_PIX_FMT_RGBA:
    case AV_PIX_FMT_ABGR:
        if (pix_fmt == AV_PIX_FMT_ARGB ||
            pix_fmt == AV_PIX_FMT_ABGR)
            be = 1;
        if (pix_fmt == AV_PIX_FMT_ABGR ||
            pix_fmt == AV_PIX_FMT_RGBA) {
            rgb[0] = 0xFF;
            rgb[1] = 0xFF00;
            rgb[2] = 0xFF0000;
        } else {
            rgb[0] = 0xFF0000;
            rgb[1] = 0xFF00;
            rgb[2] = 0xFF;
        }
        bpp      = 32;
        pixdepth = 24;
        vclass   = XWD_TRUE_COLOR;
        bpad     = 32;
        break;
    case AV_PIX_FMT_BGR24:
    case AV_PIX_FMT_RGB24:
        if (pix_fmt == AV_PIX_FMT_RGB24)
            be = 1;
        bpp      = 24;
        vclass   = XWD_TRUE_COLOR;
        bpad     = 32;
        rgb[0]   = 0xFF0000;
        rgb[1]   = 0xFF00;
        rgb[2]   = 0xFF;
        break;
    case AV_PIX_FMT_RGB565LE:
    case AV_PIX_FMT_RGB565BE:
    case AV_PIX_FMT_BGR565LE:
    case AV_PIX_FMT_BGR565BE:
        if (pix_fmt == AV_PIX_FMT_BGR565LE ||
            pix_fmt == AV_PIX_FMT_BGR565BE) {
            rgb[0] = 0x1F;
            rgb[1] = 0x7E0;
            rgb[2] = 0xF800;
        } else {
            rgb[0] = 0xF800;
            rgb[1] = 0x7E0;
            rgb[2] = 0x1F;
        }
        bpp      = 16;
        vclass   = XWD_TRUE_COLOR;
        bpad     = 16;
        break;
    case AV_PIX_FMT_RGB555LE:
    case AV_PIX_FMT_RGB555BE:
    case AV_PIX_FMT_BGR555LE:
    case AV_PIX_FMT_BGR555BE:
        if (pix_fmt == AV_PIX_FMT_BGR555LE ||
            pix_fmt == AV_PIX_FMT_BGR555BE) {
            rgb[0] = 0x1F;
            rgb[1] = 0x3E0;
            rgb[2] = 0x7C00;
        } else {
            rgb[0] = 0x7C00;
            rgb[1] = 0x3E0;
            rgb[2] = 0x1F;
        }
        bpp      = 16;
        vclass   = XWD_TRUE_COLOR;
        bpad     = 16;
        break;
    case AV_PIX_FMT_RGB8:
    case AV_PIX_FMT_BGR8:
    case AV_PIX_FMT_RGB4_BYTE:
    case AV_PIX_FMT_BGR4_BYTE:
    case AV_PIX_FMT_PAL8:
        bpp      = 8;
        vclass   = XWD_PSEUDO_COLOR;
        bpad     = 8;
        ncolors  = 256;
        break;
    case AV_PIX_FMT_GRAY8:
        bpp      = 8;
        bpad     = 8;
        vclass   = XWD_STATIC_GRAY;
        break;
    case AV_PIX_FMT_MONOWHITE:
        be       = 1;
        bitorder = 1;
        bpp      = 1;
        bpad     = 8;
        vclass   = XWD_STATIC_GRAY;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "unsupported pixel format\n");
        return AVERROR(EINVAL);
    }

    lsize       = FFALIGN(bpp * avctx->width, bpad) / 8;
    header_size = XWD_HEADER_SIZE + WINDOW_NAME_SIZE;
    out_size    = header_size + ncolors * XWD_CMAP_SIZE + avctx->height * lsize;

    if ((ret = ff_alloc_packet2(avctx, pkt, out_size, 0)) < 0)
        return ret;
    buf = pkt->data;

    p->key_frame = 1;
    p->pict_type = AV_PICTURE_TYPE_I;

    bytestream_put_be32(&buf, header_size);
    bytestream_put_be32(&buf, XWD_VERSION);   // file version
    bytestream_put_be32(&buf, XWD_Z_PIXMAP);  // pixmap format
    bytestream_put_be32(&buf, pixdepth);      // pixmap depth in pixels
    bytestream_put_be32(&buf, avctx->width);  // pixmap width in pixels
    bytestream_put_be32(&buf, avctx->height); // pixmap height in pixels
    bytestream_put_be32(&buf, 0);             // bitmap x offset
    bytestream_put_be32(&buf, be);            // byte order
    bytestream_put_be32(&buf, 32);            // bitmap unit
    bytestream_put_be32(&buf, bitorder);      // bit-order of image data
    bytestream_put_be32(&buf, bpad);          // bitmap scan-line pad in bits
    bytestream_put_be32(&buf, bpp);           // bits per pixel
    bytestream_put_be32(&buf, lsize);         // bytes per scan-line
    bytestream_put_be32(&buf, vclass);        // visual class
    bytestream_put_be32(&buf, rgb[0]);        // red mask
    bytestream_put_be32(&buf, rgb[1]);        // green mask
    bytestream_put_be32(&buf, rgb[2]);        // blue mask
    bytestream_put_be32(&buf, 8);             // size of each bitmask in bits
    bytestream_put_be32(&buf, ncolors);       // number of colors
    bytestream_put_be32(&buf, ncolors);       // number of entries in color map
    bytestream_put_be32(&buf, avctx->width);  // window width
    bytestream_put_be32(&buf, avctx->height); // window height
    bytestream_put_be32(&buf, 0);             // window upper left X coordinate
    bytestream_put_be32(&buf, 0);             // window upper left Y coordinate
    bytestream_put_be32(&buf, 0);             // window border width
    bytestream_put_buffer(&buf, WINDOW_NAME, WINDOW_NAME_SIZE);

    if (pix_fmt == AV_PIX_FMT_PAL8) {
        memcpy(pal, p->data[1], sizeof(pal));
    } else {
        avpriv_set_systematic_pal2(pal, pix_fmt);
    }

    for (i = 0; i < ncolors; i++) {
        uint32_t val;
        uint8_t red, green, blue;

        val   = pal[i];
        red   = (val >> 16) & 0xFF;
        green = (val >>  8) & 0xFF;
        blue  =  val        & 0xFF;

        bytestream_put_be32(&buf, i);         // colormap entry number
        bytestream_put_be16(&buf, red   << 8);
        bytestream_put_be16(&buf, green << 8);
        bytestream_put_be16(&buf, blue  << 8);
        bytestream_put_byte(&buf, 0x7);       // bitmask flag
        bytestream_put_byte(&buf, 0);         // padding
    }

    ptr = p->data[0];
    for (i = 0; i < avctx->height; i++) {
        bytestream_put_buffer(&buf, ptr, lsize);
        ptr += p->linesize[0];
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}