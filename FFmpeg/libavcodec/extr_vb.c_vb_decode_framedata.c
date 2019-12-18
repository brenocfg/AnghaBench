#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* prev_frame; int* frame; TYPE_3__* avctx; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ VBDecContext ;
struct TYPE_5__ {int width; int const height; } ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int*,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_line (int*,int*,int*) ; 
 int /*<<< orphan*/  check_pixel (int*,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* vb_patterns ; 

__attribute__((used)) static int vb_decode_framedata(VBDecContext *c, int offset)
{
    GetByteContext g;
    uint8_t *prev, *cur;
    int blk, blocks, t, blk2;
    int blocktypes = 0;
    int x, y, a, b;
    int pattype, pattern;
    const int width = c->avctx->width;
    uint8_t *pstart = c->prev_frame;
    uint8_t *pend   = c->prev_frame + width*c->avctx->height;

    g = c->stream;

    prev = c->prev_frame + offset;
    cur  = c->frame;

    blocks = (c->avctx->width >> 2) * (c->avctx->height >> 2);
    blk2   = 0;
    for (blk = 0; blk < blocks; blk++) {
        if (!(blk & 3)) {
            if (bytestream2_get_bytes_left(&g) < 1) {
                av_log(c->avctx, AV_LOG_ERROR, "Insufficient data\n");
                return AVERROR_INVALIDDATA;
            }
            blocktypes = bytestream2_get_byte(&g);
        }
        switch (blocktypes & 0xC0) {
        case 0x00: //skip
            for (y = 0; y < 4; y++)
                if (check_line(prev + y*width, pstart, pend))
                    memcpy(cur + y*width, prev + y*width, 4);
                else
                    memset(cur + y*width, 0, 4);
            break;
        case 0x40:
            t = bytestream2_get_byte(&g);
            if (!t) { //raw block
                if (bytestream2_get_bytes_left(&g) < 16) {
                    av_log(c->avctx, AV_LOG_ERROR, "Insufficient data\n");
                    return AVERROR_INVALIDDATA;
                }
                for (y = 0; y < 4; y++)
                    bytestream2_get_buffer(&g, cur + y * width, 4);
            } else { // motion compensation
                x = ((t & 0xF)^8) - 8;
                y = ((t >> 4) ^8) - 8;
                t = x + y*width;
                for (y = 0; y < 4; y++)
                    if (check_line(prev + t + y*width, pstart, pend))
                        memcpy(cur + y*width, prev + t + y*width, 4);
                    else
                        memset(cur + y*width, 0, 4);
            }
            break;
        case 0x80: // fill
            t = bytestream2_get_byte(&g);
            for (y = 0; y < 4; y++)
                memset(cur + y*width, t, 4);
            break;
        case 0xC0: // pattern fill
            t       = bytestream2_get_byte(&g);
            pattype = t >> 6;
            pattern = vb_patterns[t & 0x3F];
            switch (pattype) {
            case 0:
                a = bytestream2_get_byte(&g);
                b = bytestream2_get_byte(&g);
                for (y = 0; y < 4; y++)
                    for (x = 0; x < 4; x++, pattern >>= 1)
                        cur[x + y*width] = (pattern & 1) ? b : a;
                break;
            case 1:
                pattern = ~pattern;
            case 2:
                a = bytestream2_get_byte(&g);
                for (y = 0; y < 4; y++)
                    for (x = 0; x < 4; x++, pattern >>= 1)
                        if (pattern & 1 && check_pixel(prev + x + y*width, pstart, pend))
                            cur[x + y*width] = prev[x + y*width];
                        else
                            cur[x + y*width] = a;
                break;
            case 3:
                av_log(c->avctx, AV_LOG_ERROR, "Invalid opcode seen @%d\n", blk);
                return AVERROR_INVALIDDATA;
            }
            break;
        }
        blocktypes <<= 2;
        cur  += 4;
        prev += 4;
        blk2++;
        if (blk2 == (width >> 2)) {
            blk2  = 0;
            cur  += width * 3;
            prev += width * 3;
        }
    }
    return 0;
}