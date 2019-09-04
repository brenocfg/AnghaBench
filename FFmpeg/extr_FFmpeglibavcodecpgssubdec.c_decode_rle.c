#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int err_recognition; } ;
struct TYPE_7__ {int w; int h; scalar_t__* data; } ;
typedef  TYPE_1__ AVSubtitleRect ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_malloc_array (int,int) ; 
 int bytestream_get_byte (int const**) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

__attribute__((used)) static int decode_rle(AVCodecContext *avctx, AVSubtitleRect *rect,
                      const uint8_t *buf, unsigned int buf_size)
{
    const uint8_t *rle_bitmap_end;
    int pixel_count, line_count;

    rle_bitmap_end = buf + buf_size;

    rect->data[0] = av_malloc_array(rect->w, rect->h);

    if (!rect->data[0])
        return AVERROR(ENOMEM);

    pixel_count = 0;
    line_count  = 0;

    while (buf < rle_bitmap_end && line_count < rect->h) {
        uint8_t flags, color;
        int run;

        color = bytestream_get_byte(&buf);
        run   = 1;

        if (color == 0x00) {
            flags = bytestream_get_byte(&buf);
            run   = flags & 0x3f;
            if (flags & 0x40)
                run = (run << 8) + bytestream_get_byte(&buf);
            color = flags & 0x80 ? bytestream_get_byte(&buf) : 0;
        }

        if (run > 0 && pixel_count + run <= rect->w * rect->h) {
            memset(rect->data[0] + pixel_count, color, run);
            pixel_count += run;
        } else if (!run) {
            /*
             * New Line. Check if correct pixels decoded, if not display warning
             * and adjust bitmap pointer to correct new line position.
             */
            if (pixel_count % rect->w > 0) {
                av_log(avctx, AV_LOG_ERROR, "Decoded %d pixels, when line should be %d pixels\n",
                       pixel_count % rect->w, rect->w);
                if (avctx->err_recognition & AV_EF_EXPLODE) {
                    return AVERROR_INVALIDDATA;
                }
            }
            line_count++;
        }
    }

    if (pixel_count < rect->w * rect->h) {
        av_log(avctx, AV_LOG_ERROR, "Insufficient RLE data for subtitle\n");
        return AVERROR_INVALIDDATA;
    }

    ff_dlog(avctx, "Pixel Count = %d, Area = %d\n", pixel_count, rect->w * rect->h);

    return 0;
}