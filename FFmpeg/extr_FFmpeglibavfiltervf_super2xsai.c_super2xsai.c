#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int bpp; scalar_t__ hi_pixel_mask; scalar_t__ lo_pixel_mask; scalar_t__ q_hi_pixel_mask; scalar_t__ q_lo_pixel_mask; int /*<<< orphan*/  is_be; } ;
typedef  TYPE_1__ Super2xSaIContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_RB16 (unsigned char*) ; 
 scalar_t__ AV_RL16 (unsigned char*) ; 
 scalar_t__ AV_RL24 (unsigned char*) ; 
 int /*<<< orphan*/  AV_WB32 (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  AV_WL24 (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  AV_WL32 (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  AV_WN32A (unsigned char*,scalar_t__) ; 
 int FFMIN (int,int) ; 
 scalar_t__ GET_RESULT (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ INTERPOLATE (scalar_t__,scalar_t__) ; 
 scalar_t__ Q_INTERPOLATE (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void super2xsai(AVFilterContext *ctx,
                       uint8_t *src, int src_linesize,
                       uint8_t *dst, int dst_linesize,
                       int width, int height)
{
    Super2xSaIContext *s = ctx->priv;
    unsigned int x, y;
    uint32_t color[4][4];
    unsigned char *src_line[4];
    const int bpp = s->bpp;
    const uint32_t hi_pixel_mask = s->hi_pixel_mask;
    const uint32_t lo_pixel_mask = s->lo_pixel_mask;
    const uint32_t q_hi_pixel_mask = s->q_hi_pixel_mask;
    const uint32_t q_lo_pixel_mask = s->q_lo_pixel_mask;

    /* Point to the first 4 lines, first line is duplicated */
    src_line[0] = src;
    src_line[1] = src;
    src_line[2] = src + src_linesize*FFMIN(1, height-1);
    src_line[3] = src + src_linesize*FFMIN(2, height-1);

#define READ_COLOR4(dst, src_line, off) dst = *((const uint32_t *)src_line + off)
#define READ_COLOR3(dst, src_line, off) dst = AV_RL24 (src_line + 3*off)
#define READ_COLOR2(dst, src_line, off) dst = s->is_be ? AV_RB16(src_line + 2 * off) : AV_RL16(src_line + 2 * off)

    for (y = 0; y < height; y++) {
        uint8_t *dst_line[2];

        dst_line[0] = dst + dst_linesize*2*y;
        dst_line[1] = dst + dst_linesize*(2*y+1);

        switch (bpp) {
        case 4:
            READ_COLOR4(color[0][0], src_line[0], 0); color[0][1] = color[0][0]; READ_COLOR4(color[0][2], src_line[0], 1); READ_COLOR4(color[0][3], src_line[0], 2);
            READ_COLOR4(color[1][0], src_line[1], 0); color[1][1] = color[1][0]; READ_COLOR4(color[1][2], src_line[1], 1); READ_COLOR4(color[1][3], src_line[1], 2);
            READ_COLOR4(color[2][0], src_line[2], 0); color[2][1] = color[2][0]; READ_COLOR4(color[2][2], src_line[2], 1); READ_COLOR4(color[2][3], src_line[2], 2);
            READ_COLOR4(color[3][0], src_line[3], 0); color[3][1] = color[3][0]; READ_COLOR4(color[3][2], src_line[3], 1); READ_COLOR4(color[3][3], src_line[3], 2);
            break;
        case 3:
            READ_COLOR3(color[0][0], src_line[0], 0); color[0][1] = color[0][0]; READ_COLOR3(color[0][2], src_line[0], 1); READ_COLOR3(color[0][3], src_line[0], 2);
            READ_COLOR3(color[1][0], src_line[1], 0); color[1][1] = color[1][0]; READ_COLOR3(color[1][2], src_line[1], 1); READ_COLOR3(color[1][3], src_line[1], 2);
            READ_COLOR3(color[2][0], src_line[2], 0); color[2][1] = color[2][0]; READ_COLOR3(color[2][2], src_line[2], 1); READ_COLOR3(color[2][3], src_line[2], 2);
            READ_COLOR3(color[3][0], src_line[3], 0); color[3][1] = color[3][0]; READ_COLOR3(color[3][2], src_line[3], 1); READ_COLOR3(color[3][3], src_line[3], 2);
            break;
        default:
            READ_COLOR2(color[0][0], src_line[0], 0); color[0][1] = color[0][0]; READ_COLOR2(color[0][2], src_line[0], 1); READ_COLOR2(color[0][3], src_line[0], 2);
            READ_COLOR2(color[1][0], src_line[1], 0); color[1][1] = color[1][0]; READ_COLOR2(color[1][2], src_line[1], 1); READ_COLOR2(color[1][3], src_line[1], 2);
            READ_COLOR2(color[2][0], src_line[2], 0); color[2][1] = color[2][0]; READ_COLOR2(color[2][2], src_line[2], 1); READ_COLOR2(color[2][3], src_line[2], 2);
            READ_COLOR2(color[3][0], src_line[3], 0); color[3][1] = color[3][0]; READ_COLOR2(color[3][2], src_line[3], 1); READ_COLOR2(color[3][3], src_line[3], 2);
        }

        for (x = 0; x < width; x++) {
            uint32_t product1a, product1b, product2a, product2b;

//---------------------------------------  B0 B1 B2 B3    0  1  2  3
//                                         4  5* 6  S2 -> 4  5* 6  7
//                                         1  2  3  S1    8  9 10 11
//                                         A0 A1 A2 A3   12 13 14 15
//--------------------------------------
            if (color[2][1] == color[1][2] && color[1][1] != color[2][2]) {
                product2b = color[2][1];
                product1b = product2b;
            } else if (color[1][1] == color[2][2] && color[2][1] != color[1][2]) {
                product2b = color[1][1];
                product1b = product2b;
            } else if (color[1][1] == color[2][2] && color[2][1] == color[1][2]) {
                int r = 0;

                r += GET_RESULT(color[1][2], color[1][1], color[1][0], color[3][1]);
                r += GET_RESULT(color[1][2], color[1][1], color[2][0], color[0][1]);
                r += GET_RESULT(color[1][2], color[1][1], color[3][2], color[2][3]);
                r += GET_RESULT(color[1][2], color[1][1], color[0][2], color[1][3]);

                if (r > 0)
                    product1b = color[1][2];
                else if (r < 0)
                    product1b = color[1][1];
                else
                    product1b = INTERPOLATE(color[1][1], color[1][2]);

                product2b = product1b;
            } else {
                if (color[1][2] == color[2][2] && color[2][2] == color[3][1] && color[2][1] != color[3][2] && color[2][2] != color[3][0])
                    product2b = Q_INTERPOLATE(color[2][2], color[2][2], color[2][2], color[2][1]);
                else if (color[1][1] == color[2][1] && color[2][1] == color[3][2] && color[3][1] != color[2][2] && color[2][1] != color[3][3])
                    product2b = Q_INTERPOLATE(color[2][1], color[2][1], color[2][1], color[2][2]);
                else
                    product2b = INTERPOLATE(color[2][1], color[2][2]);

                if (color[1][2] == color[2][2] && color[1][2] == color[0][1] && color[1][1] != color[0][2] && color[1][2] != color[0][0])
                    product1b = Q_INTERPOLATE(color[1][2], color[1][2], color[1][2], color[1][1]);
                else if (color[1][1] == color[2][1] && color[1][1] == color[0][2] && color[0][1] != color[1][2] && color[1][1] != color[0][3])
                    product1b = Q_INTERPOLATE(color[1][2], color[1][1], color[1][1], color[1][1]);
                else
                    product1b = INTERPOLATE(color[1][1], color[1][2]);
            }

            if (color[1][1] == color[2][2] && color[2][1] != color[1][2] && color[1][0] == color[1][1] && color[1][1] != color[3][2])
                product2a = INTERPOLATE(color[2][1], color[1][1]);
            else if (color[1][1] == color[2][0] && color[1][2] == color[1][1] && color[1][0] != color[2][1] && color[1][1] != color[3][0])
                product2a = INTERPOLATE(color[2][1], color[1][1]);
            else
                product2a = color[2][1];

            if (color[2][1] == color[1][2] && color[1][1] != color[2][2] && color[2][0] == color[2][1] && color[2][1] != color[0][2])
                product1a = INTERPOLATE(color[2][1], color[1][1]);
            else if (color[1][0] == color[2][1] && color[2][2] == color[2][1] && color[2][0] != color[1][1] && color[2][1] != color[0][0])
                product1a = INTERPOLATE(color[2][1], color[1][1]);
            else
                product1a = color[1][1];

            /* Set the calculated pixels */
            switch (bpp) {
            case 4:
                AV_WN32A(dst_line[0] + x * 8,     product1a);
                AV_WN32A(dst_line[0] + x * 8 + 4, product1b);
                AV_WN32A(dst_line[1] + x * 8,     product2a);
                AV_WN32A(dst_line[1] + x * 8 + 4, product2b);
                break;
            case 3:
                AV_WL24(dst_line[0] + x * 6,     product1a);
                AV_WL24(dst_line[0] + x * 6 + 3, product1b);
                AV_WL24(dst_line[1] + x * 6,     product2a);
                AV_WL24(dst_line[1] + x * 6 + 3, product2b);
                break;
            default: // bpp = 2
                if (s->is_be) {
                    AV_WB32(dst_line[0] + x * 4, product1a | (product1b << 16));
                    AV_WB32(dst_line[1] + x * 4, product2a | (product2b << 16));
                } else {
                    AV_WL32(dst_line[0] + x * 4, product1a | (product1b << 16));
                    AV_WL32(dst_line[1] + x * 4, product2a | (product2b << 16));
                }
            }

            /* Move color matrix forward */
            color[0][0] = color[0][1]; color[0][1] = color[0][2]; color[0][2] = color[0][3];
            color[1][0] = color[1][1]; color[1][1] = color[1][2]; color[1][2] = color[1][3];
            color[2][0] = color[2][1]; color[2][1] = color[2][2]; color[2][2] = color[2][3];
            color[3][0] = color[3][1]; color[3][1] = color[3][2]; color[3][2] = color[3][3];

            if (x < width - 3) {
                x += 3;
                switch (bpp) {
                case 4:
                    READ_COLOR4(color[0][3], src_line[0], x);
                    READ_COLOR4(color[1][3], src_line[1], x);
                    READ_COLOR4(color[2][3], src_line[2], x);
                    READ_COLOR4(color[3][3], src_line[3], x);
                    break;
                case 3:
                    READ_COLOR3(color[0][3], src_line[0], x);
                    READ_COLOR3(color[1][3], src_line[1], x);
                    READ_COLOR3(color[2][3], src_line[2], x);
                    READ_COLOR3(color[3][3], src_line[3], x);
                    break;
                default:        /* case 2 */
                    READ_COLOR2(color[0][3], src_line[0], x);
                    READ_COLOR2(color[1][3], src_line[1], x);
                    READ_COLOR2(color[2][3], src_line[2], x);
                    READ_COLOR2(color[3][3], src_line[3], x);
                }
                x -= 3;
            }
        }

        /* We're done with one line, so we shift the source lines up */
        src_line[0] = src_line[1];
        src_line[1] = src_line[2];
        src_line[2] = src_line[3];

        /* Read next line */
        src_line[3] = src_line[2];
        if (y < height - 3)
            src_line[3] += src_linesize;
    } // y loop
}