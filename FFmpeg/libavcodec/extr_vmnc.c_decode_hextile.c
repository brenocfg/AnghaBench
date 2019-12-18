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
struct TYPE_3__ {int bpp2; int /*<<< orphan*/  avctx; int /*<<< orphan*/  bigendian; } ;
typedef  TYPE_1__ VmncContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int HT_BKG ; 
 int HT_CLR ; 
 int HT_FG ; 
 int HT_RAW ; 
 int HT_SUB ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paint_raw (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  paint_rect (int /*<<< orphan*/ *,int,int,int,int,int,int const,int) ; 
 int vmnc_get_pixel (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_hextile(VmncContext *c, uint8_t* dst, GetByteContext *gb,
                          int w, int h, int stride)
{
    int i, j, k;
    int bg = 0, fg = 0, rects, color, flags, xy, wh;
    const int bpp = c->bpp2;
    uint8_t *dst2;
    int bw = 16, bh = 16;

    for (j = 0; j < h; j += 16) {
        dst2 = dst;
        bw   = 16;
        if (j + 16 > h)
            bh = h - j;
        for (i = 0; i < w; i += 16, dst2 += 16 * bpp) {
            if (bytestream2_get_bytes_left(gb) <= 0) {
                av_log(c->avctx, AV_LOG_ERROR, "Premature end of data!\n");
                return AVERROR_INVALIDDATA;
            }
            if (i + 16 > w)
                bw = w - i;
            flags = bytestream2_get_byte(gb);
            if (flags & HT_RAW) {
                if (bytestream2_get_bytes_left(gb) < bw * bh * bpp) {
                    av_log(c->avctx, AV_LOG_ERROR, "Premature end of data!\n");
                    return AVERROR_INVALIDDATA;
                }
                paint_raw(dst2, bw, bh, gb, bpp, c->bigendian, stride);
            } else {
                if (flags & HT_BKG)
                    bg = vmnc_get_pixel(gb, bpp, c->bigendian);
                if (flags & HT_FG)
                    fg = vmnc_get_pixel(gb, bpp, c->bigendian);
                rects = 0;
                if (flags & HT_SUB)
                    rects = bytestream2_get_byte(gb);
                color = !!(flags & HT_CLR);

                paint_rect(dst2, 0, 0, bw, bh, bg, bpp, stride);

                if (bytestream2_get_bytes_left(gb) < rects * (color * bpp + 2)) {
                    av_log(c->avctx, AV_LOG_ERROR, "Premature end of data!\n");
                    return AVERROR_INVALIDDATA;
                }
                for (k = 0; k < rects; k++) {
                    int rect_x, rect_y, rect_w, rect_h;
                    if (color)
                        fg = vmnc_get_pixel(gb, bpp, c->bigendian);
                    xy = bytestream2_get_byte(gb);
                    wh = bytestream2_get_byte(gb);

                    rect_x = xy >> 4;
                    rect_y = xy & 0xF;
                    rect_w = (wh >> 4) + 1;
                    rect_h = (wh & 0xF) + 1;

                    if (rect_x + rect_w > w - i || rect_y + rect_h > h - j) {
                        av_log(c->avctx, AV_LOG_ERROR, "Rectangle outside picture\n");
                        return AVERROR_INVALIDDATA;
                    }

                    paint_rect(dst2, rect_x, rect_y,
                               rect_w, rect_h, fg, bpp, stride);
                }
            }
        }
        dst += stride * 16;
    }
    return 0;
}