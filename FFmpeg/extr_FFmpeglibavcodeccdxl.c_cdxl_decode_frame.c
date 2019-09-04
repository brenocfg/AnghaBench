#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_24__ {int width; int height; scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_23__ {int /*<<< orphan*/  pict_type; } ;
struct TYPE_22__ {int size; int* data; } ;
struct TYPE_21__ {int format; int bpp; int palette_size; int const* palette; int const* video; int video_size; int /*<<< orphan*/  new_video; int /*<<< orphan*/  new_video_size; TYPE_1__* avctx; scalar_t__ padded_bits; } ;
struct TYPE_20__ {scalar_t__ width; } ;
typedef  TYPE_2__ CDXLVideoContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 void* AV_RB16 (int const*) ; 
 int BIT_LINE ; 
 int BIT_PLANAR ; 
 int CHUNKY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_5__*,char*,int,...) ; 
 int /*<<< orphan*/  cdxl_decode_ham6 (TYPE_2__*,TYPE_4__* const) ; 
 int /*<<< orphan*/  cdxl_decode_ham8 (TYPE_2__*,TYPE_4__* const) ; 
 int /*<<< orphan*/  cdxl_decode_raw (TYPE_2__*,TYPE_4__* const) ; 
 int /*<<< orphan*/  cdxl_decode_rgb (TYPE_2__*,TYPE_4__* const) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__* const,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_5__*,int,int) ; 

__attribute__((used)) static int cdxl_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *pkt)
{
    CDXLVideoContext *c = avctx->priv_data;
    AVFrame * const p = data;
    int ret, w, h, encoding, aligned_width, buf_size = pkt->size;
    const uint8_t *buf = pkt->data;

    if (buf_size < 32)
        return AVERROR_INVALIDDATA;
    encoding        = buf[1] & 7;
    c->format       = buf[1] & 0xE0;
    w               = AV_RB16(&buf[14]);
    h               = AV_RB16(&buf[16]);
    c->bpp          = buf[19];
    c->palette_size = AV_RB16(&buf[20]);
    c->palette      = buf + 32;
    c->video        = c->palette + c->palette_size;
    c->video_size   = buf_size - c->palette_size - 32;

    if (c->palette_size > 512)
        return AVERROR_INVALIDDATA;
    if (buf_size < c->palette_size + 32)
        return AVERROR_INVALIDDATA;
    if (c->bpp < 1)
        return AVERROR_INVALIDDATA;
    if (c->format != BIT_PLANAR && c->format != BIT_LINE && c->format != CHUNKY) {
        avpriv_request_sample(avctx, "Pixel format 0x%0x", c->format);
        return AVERROR_PATCHWELCOME;
    }

    if ((ret = ff_set_dimensions(avctx, w, h)) < 0)
        return ret;

    if (c->format == CHUNKY)
        aligned_width = avctx->width;
    else
        aligned_width = FFALIGN(c->avctx->width, 16);
    c->padded_bits  = aligned_width - c->avctx->width;
    if (c->video_size < aligned_width * avctx->height * (int64_t)c->bpp / 8)
        return AVERROR_INVALIDDATA;
    if (!encoding && c->palette_size && c->bpp <= 8 && c->format != CHUNKY) {
        avctx->pix_fmt = AV_PIX_FMT_PAL8;
    } else if (encoding == 1 && (c->bpp == 6 || c->bpp == 8) && c->format != CHUNKY) {
        if (c->palette_size != (1 << (c->bpp - 1)))
            return AVERROR_INVALIDDATA;
        avctx->pix_fmt = AV_PIX_FMT_BGR24;
    } else if (!encoding && c->bpp == 24 && c->format == CHUNKY &&
               !c->palette_size) {
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
    } else {
        avpriv_request_sample(avctx, "Encoding %d, bpp %d and format 0x%x",
                              encoding, c->bpp, c->format);
        return AVERROR_PATCHWELCOME;
    }

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;
    p->pict_type = AV_PICTURE_TYPE_I;

    if (encoding) {
        av_fast_padded_malloc(&c->new_video, &c->new_video_size,
                              h * w + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!c->new_video)
            return AVERROR(ENOMEM);
        if (c->bpp == 8)
            cdxl_decode_ham8(c, p);
        else
            cdxl_decode_ham6(c, p);
    } else if (avctx->pix_fmt == AV_PIX_FMT_PAL8) {
        cdxl_decode_rgb(c, p);
    } else {
        cdxl_decode_raw(c, p);
    }
    *got_frame = 1;

    return buf_size;
}