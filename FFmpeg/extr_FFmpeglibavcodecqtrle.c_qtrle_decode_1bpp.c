#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_7__ {int /*<<< orphan*/  g; TYPE_2__* avctx; TYPE_1__* frame; } ;
struct TYPE_6__ {int height; } ;
struct TYPE_5__ {int* linesize; int** data; } ;
typedef  TYPE_3__ QtrleContext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_PIXEL_PTR (int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtrle_decode_1bpp(QtrleContext *s, int row_ptr, int lines_to_change)
{
    int rle_code;
    int pixel_ptr;
    int row_inc = s->frame->linesize[0];
    uint8_t pi0, pi1;  /* 2 8-pixel values */
    uint8_t *rgb = s->frame->data[0];
    int pixel_limit = s->frame->linesize[0] * s->avctx->height;
    int skip;
    /* skip & 0x80 appears to mean 'start a new line', which can be interpreted
     * as 'go to next line' during the decoding of a frame but is 'go to first
     * line' at the beginning. Since we always interpret it as 'go to next line'
     * in the decoding loop (which makes code simpler/faster), the first line
     * would not be counted, so we count one more.
     * See: https://trac.ffmpeg.org/ticket/226
     * In the following decoding loop, row_ptr will be the position of the
     * current row. */

    row_ptr  -= row_inc;
    pixel_ptr = row_ptr;
    lines_to_change++;
    while (lines_to_change) {
        skip     =              bytestream2_get_byte(&s->g);
        rle_code = (int8_t)bytestream2_get_byte(&s->g);
        if (rle_code == 0)
            break;
        if(skip & 0x80) {
            lines_to_change--;
            row_ptr += row_inc;
            pixel_ptr = row_ptr + 2 * 8 * (skip & 0x7f);
        } else
            pixel_ptr += 2 * 8 * skip;
        CHECK_PIXEL_PTR(0);  /* make sure pixel_ptr is positive */

        if(rle_code == -1)
            continue;

        if (rle_code < 0) {
            /* decode the run length code */
            rle_code = -rle_code;
            /* get the next 2 bytes from the stream, treat them as groups
             * of 8 pixels, and output them rle_code times */

            pi0 = bytestream2_get_byte(&s->g);
            pi1 = bytestream2_get_byte(&s->g);
            CHECK_PIXEL_PTR(rle_code * 2 * 8);

            while (rle_code--) {
                rgb[pixel_ptr++] = (pi0 >> 7) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 6) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 5) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 4) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 3) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 2) & 0x01;
                rgb[pixel_ptr++] = (pi0 >> 1) & 0x01;
                rgb[pixel_ptr++] =  pi0       & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 7) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 6) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 5) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 4) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 3) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 2) & 0x01;
                rgb[pixel_ptr++] = (pi1 >> 1) & 0x01;
                rgb[pixel_ptr++] =  pi1       & 0x01;
            }
        } else {
            /* copy the same pixel directly to output 2 times */
            rle_code *= 2;
            CHECK_PIXEL_PTR(rle_code * 8);

            while (rle_code--) {
                int x = bytestream2_get_byte(&s->g);
                rgb[pixel_ptr++] = (x >> 7) & 0x01;
                rgb[pixel_ptr++] = (x >> 6) & 0x01;
                rgb[pixel_ptr++] = (x >> 5) & 0x01;
                rgb[pixel_ptr++] = (x >> 4) & 0x01;
                rgb[pixel_ptr++] = (x >> 3) & 0x01;
                rgb[pixel_ptr++] = (x >> 2) & 0x01;
                rgb[pixel_ptr++] = (x >> 1) & 0x01;
                rgb[pixel_ptr++] =  x       & 0x01;
            }
        }
    }
}