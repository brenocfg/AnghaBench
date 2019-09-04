#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int ff_rle_count_pixels (int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_rle_encode(uint8_t *outbuf, int out_size, const uint8_t *ptr, int bpp,
                  int w, int add_rep, int xor_rep, int add_raw, int xor_raw)
{
    int count, x;
    uint8_t *out = outbuf;

    for (x = 0; x < w; x += count) {
        /* see if we can encode the next set of pixels with RLE */
        if ((count = ff_rle_count_pixels(ptr, w - x, bpp, 1)) > 1) {
            if (out + bpp + 1 > outbuf + out_size)
                return -1;

            *out++ = (count ^ xor_rep) + add_rep;
            memcpy(out, ptr, bpp);
            out += bpp;
        } else {
            /* fall back on uncompressed */
            count = ff_rle_count_pixels(ptr, w - x, bpp, 0);
            if (out + bpp * count >= outbuf + out_size)
                return -1;

            *out++ = (count ^ xor_raw) + add_raw;
            memcpy(out, ptr, bpp * count);
            out += bpp * count;
        }

        ptr += count * bpp;
    }

    return out - outbuf;
}