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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int swizzle_x (int const) ; 
 int swizzle_y (unsigned int) ; 

void gfx_slow_swizzling_blit(uint32_t *buffer, uint32_t *image, int w, int h, int tx, int ty, bool blend)
{
    uint32_t *dest = buffer;
    uint32_t *src = image;
    int x0 = tx;
    int y0 = ty;
    int x1 = x0 + w;
    int y1 = y0 + h;
    const uint32_t tile_height = 128;
    const uint32_t padded_width = 128 * 10;

    /* we're doing this in pixels - should just shift the swizzles instead */
    uint32_t offs_x0 = swizzle_x(x0);
    uint32_t offs_y = swizzle_y(y0);
    uint32_t x_mask = swizzle_x(~0u);
    uint32_t y_mask = swizzle_y(~0u);
    uint32_t incr_y = swizzle_x(padded_width);

    /* step offs_x0 to the right row of tiles */
    offs_x0 += incr_y * (y0 / tile_height);

    uint32_t x, y;
    for (y = y0; y < y1; y++)
    {
        uint32_t *dest_line = dest + offs_y;
        uint32_t offs_x = offs_x0;

        for (x = x0; x < x1; x++)
        {
            uint32_t pixel = *src++;
            if (blend) /* supercheap masking */
            {
                uint32_t dst = dest_line[offs_x];
                uint8_t src_a = ((pixel & 0xFF000000) >> 24);

                if (src_a > 0)
                    pixel &= 0x00FFFFFF;
                else
                    pixel = dst;
            }

            dest_line[offs_x] = pixel;

            offs_x = (offs_x - x_mask) & x_mask;
        }

        offs_y = (offs_y - y_mask) & y_mask;
        if (!offs_y)
            offs_x0 += incr_y; /* wrap into next tile row */
    }
}