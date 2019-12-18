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
 int apply_mask_fudge_factor (int) ; 

__attribute__((used)) static void convert_mask_to_strength_mask(uint8_t *data, int linesize,
                                          int w, int h, int min_val,
                                          int *max_mask_size)
{
    int x, y;

    /* How many times we've gone through the loop. Used in the
       in-place erosion algorithm and to get us max_mask_size later on. */
    int current_pass = 0;

    /* set all non-zero values to 1 */
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
            data[y*linesize + x] = data[y*linesize + x] > min_val;

    /* For each pass, if a pixel is itself the same value as the
       current pass, and its four neighbors are too, then it is
       incremented. If no pixels are incremented by the end of the
       pass, then we go again. Edge pixels are counted as always
       excluded (this should be true anyway for any sane mask, but if
       it isn't this will ensure that we eventually exit). */
    while (1) {
        /* If this doesn't get set by the end of this pass, then we're done. */
        int has_anything_changed = 0;
        uint8_t *current_pixel0 = data + 1 + linesize, *current_pixel;
        current_pass++;

        for (y = 1; y < h-1; y++) {
            current_pixel = current_pixel0;
            for (x = 1; x < w-1; x++) {
                /* Apply the in-place erosion transform. It is based
                   on the following two premises:
                   1 - Any pixel that fails 1 erosion will fail all
                       future erosions.

                   2 - Only pixels having survived all erosions up to
                       the present will be >= to current_pass.
                   It doesn't matter if it survived the current pass,
                   failed it, or hasn't been tested yet.  By using >=
                   instead of ==, we allow the algorithm to work in
                   place. */
                if ( *current_pixel      >= current_pass &&
                    *(current_pixel + 1) >= current_pass &&
                    *(current_pixel - 1) >= current_pass &&
                    *(current_pixel + linesize) >= current_pass &&
                    *(current_pixel - linesize) >= current_pass) {
                    /* Increment the value since it still has not been
                     * eroded, as evidenced by the if statement that
                     * just evaluated to true. */
                    (*current_pixel)++;
                    has_anything_changed = 1;
                }
                current_pixel++;
            }
            current_pixel0 += linesize;
        }
        if (!has_anything_changed)
            break;
    }

    /* Apply the fudge factor, which will increase the size of the
     * mask a little to reduce jitter at the cost of more blur. */
    for (y = 1; y < h - 1; y++)
        for (x = 1; x < w - 1; x++)
            data[(y * linesize) + x] = apply_mask_fudge_factor(data[(y * linesize) + x]);

    /* As a side-effect, we now know the maximum mask size, which
     * we'll use to generate our masks. */
    /* Apply the fudge factor to this number too, since we must ensure
     * that enough masks are generated. */
    *max_mask_size = apply_mask_fudge_factor(current_pass + 1);
}