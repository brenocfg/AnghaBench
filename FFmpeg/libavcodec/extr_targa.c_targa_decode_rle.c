#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ TargaContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/ * advance_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int targa_decode_rle(AVCodecContext *avctx, TargaContext *s,
                            uint8_t *start, int w, int h, int stride,
                            int bpp, int interleave)
{
    int x, y;
    int depth = (bpp + 1) >> 3;
    int type, count;
    uint8_t *line = start;
    uint8_t *dst  = line;

    x = y = count = 0;
    while (dst) {
        if (bytestream2_get_bytes_left(&s->gb) <= 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Ran ouf of data before end-of-image\n");
            return AVERROR_INVALIDDATA;
        }
        type  = bytestream2_get_byteu(&s->gb);
        count = (type & 0x7F) + 1;
        type &= 0x80;
        if (!type) {
            do {
                int n  = FFMIN(count, w - x);
                bytestream2_get_buffer(&s->gb, dst, n * depth);
                count -= n;
                dst   += n * depth;
                x     += n;
                if (x == w) {
                    x    = 0;
                    dst = line = advance_line(start, line, stride, &y, h, interleave);
                }
            } while (dst && count > 0);
        } else {
            uint8_t tmp[4];
            bytestream2_get_buffer(&s->gb, tmp, depth);
            do {
                int n  = FFMIN(count, w - x);
                count -= n;
                x     += n;
                do {
                    memcpy(dst, tmp, depth);
                    dst += depth;
                } while (--n);
                if (x == w) {
                    x    = 0;
                    dst = line = advance_line(start, line, stride, &y, h, interleave);
                }
            } while (dst && count > 0);
        }
    }

    if (count) {
        av_log(avctx, AV_LOG_ERROR, "Packet went out of bounds\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}