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
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,int**,int) ; 

__attribute__((used)) static inline void qtrle_decode_2n4bpp(QtrleContext *s, int row_ptr,
                                       int lines_to_change, int bpp)
{
    int rle_code, i;
    int pixel_ptr;
    int row_inc = s->frame->linesize[0];
    uint8_t pi[16];  /* 16 palette indices */
    uint8_t *rgb = s->frame->data[0];
    int pixel_limit = s->frame->linesize[0] * s->avctx->height;
    int num_pixels = (bpp == 4) ? 8 : 16;

    while (lines_to_change--) {
        pixel_ptr = row_ptr + (num_pixels * (bytestream2_get_byte(&s->g) - 1));
        CHECK_PIXEL_PTR(0);

        while ((rle_code = (int8_t)bytestream2_get_byte(&s->g)) != -1) {
            if (bytestream2_get_bytes_left(&s->g) < 1)
                return;
            if (rle_code == 0) {
                /* there's another skip code in the stream */
                pixel_ptr += (num_pixels * (bytestream2_get_byte(&s->g) - 1));
                CHECK_PIXEL_PTR(0);  /* make sure pixel_ptr is positive */
            } else if (rle_code < 0) {
                /* decode the run length code */
                rle_code = -rle_code;
                /* get the next 4 bytes from the stream, treat them as palette
                 * indexes, and output them rle_code times */
                for (i = num_pixels-1; i >= 0; i--) {
                    pi[num_pixels-1-i] = (bytestream2_peek_byte(&s->g) >> ((i*bpp) & 0x07)) & ((1<<bpp)-1);
                    bytestream2_skip(&s->g, ((i & ((num_pixels>>2)-1)) == 0));
                }
                CHECK_PIXEL_PTR(rle_code * num_pixels);
                while (rle_code--) {
                    memcpy(&rgb[pixel_ptr], &pi, num_pixels);
                    pixel_ptr += num_pixels;
                }
            } else {
                /* copy the same pixel directly to output 4 times */
                rle_code *= 4;
                CHECK_PIXEL_PTR(rle_code*(num_pixels>>2));
                while (rle_code--) {
                    if(bpp == 4) {
                        int x = bytestream2_get_byte(&s->g);
                        rgb[pixel_ptr++] = (x >> 4) & 0x0f;
                        rgb[pixel_ptr++] =  x       & 0x0f;
                    } else {
                        int x = bytestream2_get_byte(&s->g);
                        rgb[pixel_ptr++] = (x >> 6) & 0x03;
                        rgb[pixel_ptr++] = (x >> 4) & 0x03;
                        rgb[pixel_ptr++] = (x >> 2) & 0x03;
                        rgb[pixel_ptr++] =  x       & 0x03;
                    }
                }
            }
        }
        row_ptr += row_inc;
    }
}