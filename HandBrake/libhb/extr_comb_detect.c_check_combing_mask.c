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
struct TYPE_7__ {int block_threshold; int block_width; int block_height; int comb_check_complete; int mask_box_x; int mask_box_y; int* block_score; TYPE_2__* mask; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_6__ {TYPE_1__* plane; } ;
struct TYPE_5__ {int stride; int width; int* data; } ;

/* Variables and functions */

__attribute__((used)) static void check_combing_mask( hb_filter_private_t * pv, int segment,
                                int start, int stop )
{
    /* Go through the mask in X*Y blocks. If any of these windows
       have threshold or more combed pixels, consider the whole
       frame to be combed and send it on to be deinterlaced.     */

    /* Block mask threshold -- The number of pixels
       in a block_width * block_height window of
       he mask that need to show combing for the
       whole frame to be seen as such.            */
    int threshold       = pv->block_threshold;
    int block_width     = pv->block_width;
    int block_height    = pv->block_height;
    int block_x, block_y;
    int block_score = 0;
    uint8_t * mask_p;
    int x, y, pp;

    for (pp = 0; pp < 1; pp++)
    {
        int stride = pv->mask->plane[pp].stride;
        int width = pv->mask->plane[pp].width;

        for (y = start; y < (stop - block_height + 1); y = y + block_height)
        {
            for (x = 0; x < (width - block_width); x = x + block_width)
            {
                block_score = 0;

                for (block_y = 0; block_y < block_height; block_y++)
                {
                    int mask_y = y + block_y;
                    mask_p = &pv->mask->plane[pp].data[mask_y * stride + x];

                    for (block_x = 0; block_x < block_width; block_x++)
                    {
                        /* We only want to mark a pixel in a block as combed
                           if the adjacent pixels are as well. Got to
                           handle the sides separately.       */
                        if ((x + block_x) == 0)
                        {
                            block_score += mask_p[0] & mask_p[1];
                        }
                        else if ((x + block_x) == (width -1))
                        {
                            block_score += mask_p[-1] & mask_p[0];
                        }
                        else
                        {
                            block_score += mask_p[-1] & mask_p[0] & mask_p[1];
                        }

                        mask_p++;
                    }
                }

                if (pv->comb_check_complete)
                {
                    // Some other thread found coming before this one
                    return;
                }

                if (block_score >= ( threshold / 2 ))
                {
                    pv->mask_box_x = x;
                    pv->mask_box_y = y;

                    pv->block_score[segment] = block_score;
                    if (block_score > threshold)
                    {
                        pv->comb_check_complete = 1;
                        return;
                    }
                }
            }
        }
    }
}