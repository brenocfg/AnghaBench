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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {scalar_t__ pix_fmt; } ;
struct TYPE_15__ {int palette_has_changed; int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * linesize; scalar_t__* data; } ;
struct TYPE_14__ {int size; scalar_t__ data; } ;
struct TYPE_13__ {int format; unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ PixHeader ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_0RGB ; 
 scalar_t__ AV_PIX_FMT_ARGB ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 scalar_t__ AV_PIX_FMT_RGB555BE ; 
 scalar_t__ AV_PIX_FMT_RGB565BE ; 
 scalar_t__ AV_PIX_FMT_YA8 ; 
 unsigned int HEADER1_CHUNK ; 
 unsigned int HEADER2_CHUNK ; 
 unsigned int IMAGE_DATA_CHUNK ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,...) ; 
 unsigned int bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be32u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pix_decode_header (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  std_pal_table ; 

__attribute__((used)) static int pix_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AVFrame *frame = data;

    int ret, i;
    GetByteContext gb;

    unsigned int bytes_pp;
    unsigned int magic[4];
    unsigned int chunk_type;
    unsigned int data_len;
    unsigned int bytes_per_scanline;
    unsigned int bytes_left;
    PixHeader hdr;

    bytestream2_init(&gb, avpkt->data, avpkt->size);

    magic[0] = bytestream2_get_be32(&gb);
    magic[1] = bytestream2_get_be32(&gb);
    magic[2] = bytestream2_get_be32(&gb);
    magic[3] = bytestream2_get_be32(&gb);

    if (magic[0] != 0x12 ||
        magic[1] != 0x08 ||
        magic[2] != 0x02 ||
        magic[3] != 0x02) {
        av_log(avctx, AV_LOG_ERROR, "Not a BRender PIX file.\n");
        return AVERROR_INVALIDDATA;
    }

    chunk_type = bytestream2_get_be32(&gb);
    if (chunk_type != HEADER1_CHUNK && chunk_type != HEADER2_CHUNK) {
        av_log(avctx, AV_LOG_ERROR, "Invalid chunk type %d.\n", chunk_type);
        return AVERROR_INVALIDDATA;
    }

    ret = pix_decode_header(&hdr, &gb);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Invalid header length.\n");
        return ret;
    }
    switch (hdr.format) {
    case 3:
        avctx->pix_fmt = AV_PIX_FMT_PAL8;
        bytes_pp = 1;
        break;
    case 4:
        avctx->pix_fmt = AV_PIX_FMT_RGB555BE;
        bytes_pp = 2;
        break;
    case 5:
        avctx->pix_fmt = AV_PIX_FMT_RGB565BE;
        bytes_pp = 2;
        break;
    case 6:
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
        bytes_pp = 3;
        break;
    case 7:
        avctx->pix_fmt = AV_PIX_FMT_0RGB;
        bytes_pp = 4;
        break;
    case 8: // ARGB
        avctx->pix_fmt = AV_PIX_FMT_ARGB;
        bytes_pp = 4;
        break;
    case 18:
        avctx->pix_fmt = AV_PIX_FMT_YA8;
        bytes_pp = 2;
        break;
    default:
        avpriv_request_sample(avctx, "Format %d", hdr.format);
        return AVERROR_PATCHWELCOME;
    }
    bytes_per_scanline = bytes_pp * hdr.width;

    if (bytestream2_get_bytes_left(&gb) < hdr.height * bytes_per_scanline)
        return AVERROR_INVALIDDATA;

    if ((ret = ff_set_dimensions(avctx, hdr.width, hdr.height)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    chunk_type = bytestream2_get_be32(&gb);

    if (avctx->pix_fmt == AV_PIX_FMT_PAL8 &&
        (chunk_type == HEADER1_CHUNK ||
         chunk_type == HEADER2_CHUNK)) {
        /* read palette data from data[1] */
        PixHeader palhdr;
        uint32_t *pal_out = (uint32_t *)frame->data[1];

        ret = pix_decode_header(&palhdr, &gb);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "Invalid palette header length.\n");
            return ret;
        }
        if (palhdr.format != 7)
            avpriv_request_sample(avctx, "Palette not in RGB format");

        chunk_type = bytestream2_get_be32(&gb);
        data_len = bytestream2_get_be32(&gb);
        bytestream2_skip(&gb, 8);
        if (chunk_type != IMAGE_DATA_CHUNK || data_len != 1032 ||
            bytestream2_get_bytes_left(&gb) < 1032) {
            av_log(avctx, AV_LOG_ERROR, "Invalid palette data.\n");
            return AVERROR_INVALIDDATA;
        }
        // palette data is surrounded by 8 null bytes (both top and bottom)
        // convert 0RGB to machine endian format (ARGB32)
        for (i = 0; i < 256; ++i)
            *pal_out++ = (0xFFU << 24) | bytestream2_get_be32u(&gb);
        bytestream2_skip(&gb, 8);

        frame->palette_has_changed = 1;

        chunk_type = bytestream2_get_be32(&gb);
    } else if (avctx->pix_fmt == AV_PIX_FMT_PAL8) {
        /* no palette supplied, use the default one */
        uint32_t *pal_out = (uint32_t *)frame->data[1];

        // TODO: add an AVOption to load custom palette files
        av_log(avctx, AV_LOG_WARNING,
               "Using default palette, colors might be off.\n");
        memcpy(pal_out, std_pal_table, sizeof(uint32_t) * 256);

        frame->palette_has_changed = 1;
    }

    data_len = bytestream2_get_be32(&gb);
    bytestream2_skip(&gb, 8);

    // read the image data to the buffer
    bytes_left = bytestream2_get_bytes_left(&gb);

    if (chunk_type != IMAGE_DATA_CHUNK || data_len != bytes_left ||
        bytes_left / bytes_per_scanline < hdr.height) {
        av_log(avctx, AV_LOG_ERROR, "Invalid image data.\n");
        return AVERROR_INVALIDDATA;
    }

    av_image_copy_plane(frame->data[0], frame->linesize[0],
                        avpkt->data + bytestream2_tell(&gb),
                        bytes_per_scanline,
                        bytes_per_scanline, hdr.height);

    frame->pict_type = AV_PICTURE_TYPE_I;
    frame->key_frame = 1;
    *got_frame = 1;

    return avpkt->size;
}