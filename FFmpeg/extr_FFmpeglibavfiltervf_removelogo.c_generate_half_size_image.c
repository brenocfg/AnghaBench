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
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  convert_mask_to_strength_mask (int*,int,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void generate_half_size_image(const uint8_t *src_data, int src_linesize,
                                     uint8_t *dst_data, int dst_linesize,
                                     int src_w, int src_h,
                                     int *max_mask_size)
{
    int x, y;

    /* Copy over the image data, using the average of 4 pixels for to
     * calculate each downsampled pixel. */
    for (y = 0; y < src_h/2; y++) {
        for (x = 0; x < src_w/2; x++) {
            /* Set the pixel if there exists a non-zero value in the
             * source pixels, else clear it. */
            dst_data[(y * dst_linesize) + x] =
                src_data[((y << 1) * src_linesize) + (x << 1)] ||
                src_data[((y << 1) * src_linesize) + (x << 1) + 1] ||
                src_data[(((y << 1) + 1) * src_linesize) + (x << 1)] ||
                src_data[(((y << 1) + 1) * src_linesize) + (x << 1) + 1];
            dst_data[(y * dst_linesize) + x] = FFMIN(1, dst_data[(y * dst_linesize) + x]);
        }
    }

    convert_mask_to_strength_mask(dst_data, dst_linesize,
                                  src_w/2, src_h/2, 0, max_mask_size);
}