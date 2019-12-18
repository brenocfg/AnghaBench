#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  tilebuffer; TYPE_1__* refframe; int /*<<< orphan*/  gbc; } ;
struct TYPE_7__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_2__ TDSCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MKTAG (char,char,char,char) ; 
 int TDSB_HEADER_SIZE ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_reallocp (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int tdsc_decode_jpeg_tile (TYPE_3__*,int,int,int,int,int) ; 

__attribute__((used)) static int tdsc_decode_tiles(AVCodecContext *avctx, int number_tiles)
{
    TDSCContext *ctx = avctx->priv_data;
    int i;

    /* Iterate over the number of tiles */
    for (i = 0; i < number_tiles; i++) {
        int tile_size;
        int tile_mode;
        int x, y, w, h;
        int ret;

        if (bytestream2_get_bytes_left(&ctx->gbc) < 4 ||
            bytestream2_get_le32(&ctx->gbc) != MKTAG('T','D','S','B') ||
            bytestream2_get_bytes_left(&ctx->gbc) < TDSB_HEADER_SIZE - 4) {
            av_log(avctx, AV_LOG_ERROR, "TDSB tag is too small.\n");
            return AVERROR_INVALIDDATA;
        }

        tile_size = bytestream2_get_le32(&ctx->gbc);
        if (bytestream2_get_bytes_left(&ctx->gbc) < tile_size)
            return AVERROR_INVALIDDATA;

        tile_mode = bytestream2_get_le32(&ctx->gbc);
        bytestream2_skip(&ctx->gbc, 4); // unknown
        x = bytestream2_get_le32(&ctx->gbc);
        y = bytestream2_get_le32(&ctx->gbc);
        w = bytestream2_get_le32(&ctx->gbc) - x;
        h = bytestream2_get_le32(&ctx->gbc) - y;

        if (x >= ctx->width || y >= ctx->height) {
            av_log(avctx, AV_LOG_ERROR,
                   "Invalid tile position (%d.%d outside %dx%d).\n",
                   x, y, ctx->width, ctx->height);
            return AVERROR_INVALIDDATA;
        }
        if (x + w > ctx->width || y + h > ctx->height) {
            av_log(avctx, AV_LOG_ERROR,
                   "Invalid tile size %dx%d\n", w, h);
            return AVERROR_INVALIDDATA;
        }

        ret = av_reallocp(&ctx->tilebuffer, tile_size);
        if (!ctx->tilebuffer)
            return ret;

        bytestream2_get_buffer(&ctx->gbc, ctx->tilebuffer, tile_size);

        if (tile_mode == MKTAG('G','E','P','J')) {
            /* Decode JPEG tile and copy it in the reference frame */
            ret = tdsc_decode_jpeg_tile(avctx, tile_size, x, y, w, h);
            if (ret < 0)
                return ret;
        } else if (tile_mode == MKTAG(' ','W','A','R')) {
            /* Just copy the buffer to output */
            av_image_copy_plane(ctx->refframe->data[0] + x * 3 +
                                ctx->refframe->linesize[0] * y,
                                ctx->refframe->linesize[0], ctx->tilebuffer,
                                w * 3, w * 3, h);
        } else {
            av_log(avctx, AV_LOG_ERROR, "Unknown tile type %08x.\n", tile_mode);
            return AVERROR_INVALIDDATA;
        }
        av_log(avctx, AV_LOG_DEBUG, "Tile %d, %dx%d (%d.%d)\n", i, w, h, x, y);
    }

    return 0;
}