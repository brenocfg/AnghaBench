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
typedef  int uint8_t ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int FFMIN (int,int) ; 

__attribute__((used)) static unsigned int blur_pixel(int ***mask,
                               const uint8_t *mask_data, int mask_linesize,
                               uint8_t       *image_data, int image_linesize,
                               int w, int h, int x, int y)
{
    /* Mask size tells how large a circle to use. The radius is about
     * (slightly larger than) mask size. */
    int mask_size;
    int start_posx, start_posy, end_posx, end_posy;
    int i, j;
    unsigned int accumulator = 0, divisor = 0;
    /* What pixel we are reading out of the circular blur mask. */
    const uint8_t *image_read_position;
    /* What pixel we are reading out of the filter image. */
    const uint8_t *mask_read_position;

    /* Prepare our bounding rectangle and clip it if need be. */
    mask_size  = mask_data[y * mask_linesize + x];
    start_posx = FFMAX(0, x - mask_size);
    start_posy = FFMAX(0, y - mask_size);
    end_posx   = FFMIN(w - 1, x + mask_size);
    end_posy   = FFMIN(h - 1, y + mask_size);

    image_read_position = image_data + image_linesize * start_posy + start_posx;
    mask_read_position  = mask_data  + mask_linesize  * start_posy + start_posx;

    for (j = start_posy; j <= end_posy; j++) {
        for (i = start_posx; i <= end_posx; i++) {
            /* Check if this pixel is in the mask or not. Only use the
             * pixel if it is not. */
            if (!(*mask_read_position) && mask[mask_size][i - start_posx][j - start_posy]) {
                accumulator += *image_read_position;
                divisor++;
            }

            image_read_position++;
            mask_read_position++;
        }

        image_read_position += (image_linesize - ((end_posx + 1) - start_posx));
        mask_read_position  += (mask_linesize - ((end_posx + 1) - start_posx));
    }

    /* If divisor is 0, it means that not a single pixel is outside of
       the logo, so we have no data.  Else we need to normalise the
       data using the divisor. */
    return divisor == 0 ? 255:
        (accumulator + (divisor / 2)) / divisor;  /* divide, taking into account average rounding error */
}