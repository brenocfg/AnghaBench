#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int prefiltered; int* mem; int* image; int border; int w; int h; int* mem_pre; int* image_pre; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ BorderedPlane ;

/* Variables and functions */
 int const NLMEANS_PREFILTER_MODE_CSM3X3 ; 
 int const NLMEANS_PREFILTER_MODE_CSM5X5 ; 
 int const NLMEANS_PREFILTER_MODE_EDGEBOOST ; 
 int const NLMEANS_PREFILTER_MODE_MEAN3X3 ; 
 int const NLMEANS_PREFILTER_MODE_MEAN5X5 ; 
 int const NLMEANS_PREFILTER_MODE_MEDIAN3X3 ; 
 int const NLMEANS_PREFILTER_MODE_MEDIAN5X5 ; 
 int const NLMEANS_PREFILTER_MODE_PASSTHRU ; 
 int const NLMEANS_PREFILTER_MODE_REDUCE25 ; 
 int const NLMEANS_PREFILTER_MODE_REDUCE50 ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 int* malloc (int const) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int const) ; 
 int /*<<< orphan*/  nlmeans_border (int*,int const,int const,int const) ; 
 int /*<<< orphan*/  nlmeans_filter_csm (int const*,int*,int const,int const,int const,int) ; 
 int /*<<< orphan*/  nlmeans_filter_edgeboost (int const*,int*,int const,int const,int const) ; 
 int /*<<< orphan*/  nlmeans_filter_mean (int const*,int*,int const,int const,int const,int) ; 
 int /*<<< orphan*/  nlmeans_filter_median (int const*,int*,int const,int const,int const,int) ; 

__attribute__((used)) static void nlmeans_prefilter(BorderedPlane *src,
                              const int filter_type)
{
    hb_lock(src->mutex);
    if (src->prefiltered == 1)
    {
        hb_unlock(src->mutex);
        return;
    }

    if (filter_type & NLMEANS_PREFILTER_MODE_MEAN3X3   ||
        filter_type & NLMEANS_PREFILTER_MODE_MEAN5X5   ||
        filter_type & NLMEANS_PREFILTER_MODE_MEDIAN3X3 ||
        filter_type & NLMEANS_PREFILTER_MODE_MEDIAN5X5 ||
        filter_type & NLMEANS_PREFILTER_MODE_CSM3X3    ||
        filter_type & NLMEANS_PREFILTER_MODE_CSM5X5)
    {

        // Source image
        const uint8_t *mem   = src->mem;
        const uint8_t *image = src->image;
        const int border     = src->border;
        const int w          = src->w;
        const int h          = src->h;
        const int bw         = w + 2 * border;
        const int bh         = h + 2 * border;

        // Duplicate plane
        uint8_t *mem_pre = malloc(bw * bh * sizeof(uint8_t));
        uint8_t *image_pre = mem_pre + border + bw * border;
        for (int y = 0; y < h; y++)
        {
            memcpy(mem_pre + y * bw, mem + y * bw, bw);
        }

        // Filter plane; should already have at least 2px extra border on each side
        if (filter_type & NLMEANS_PREFILTER_MODE_CSM5X5)
        {
            // CSM 5x5
            nlmeans_filter_csm(image, image_pre, w, h, border, 5);
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_CSM3X3)
        {
            // CSM 3x3
            nlmeans_filter_csm(image, image_pre, w, h, border, 3);
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_MEDIAN5X5)
        {
            // Median 5x5
            nlmeans_filter_median(image, image_pre, w, h, border, 5);
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_MEDIAN3X3)
        {
            // Median 3x3
            nlmeans_filter_median(image, image_pre, w, h, border, 3);
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_MEAN5X5)
        {
            // Mean 5x5
            nlmeans_filter_mean(image, image_pre, w, h, border, 5);
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_MEAN3X3)
        {
            // Mean 3x3
            nlmeans_filter_mean(image, image_pre, w, h, border, 3);
        }

        // Restore edges
        if (filter_type & NLMEANS_PREFILTER_MODE_EDGEBOOST)
        {
            nlmeans_filter_edgeboost(image, image_pre, w, h, border);
        }

        // Blend source and destination for lesser effect
        int wet = 1;
        int dry = 0;
        if (filter_type & NLMEANS_PREFILTER_MODE_REDUCE50 &&
            filter_type & NLMEANS_PREFILTER_MODE_REDUCE25)
        {
            wet = 1;
            dry = 3;
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_REDUCE50)
        {
            wet = 1;
            dry = 1;
        }
        else if (filter_type & NLMEANS_PREFILTER_MODE_REDUCE25)
        {
            wet = 3;
            dry = 1;
        }
        if (dry > 0)
        {
            for (int y = 0; y < bh; y++)
            {
                for (int x = 0; x < bw; x++)
                {
                    *(mem_pre + bw*y + x) = (uint8_t)((wet * *(mem_pre + bw*y + x) + dry * *(mem + bw*y + x)) / (wet + dry));
                }
            }
        }

        // Recreate borders
        nlmeans_border(mem_pre, w, h, border);

        // Assign result
        src->mem_pre   = mem_pre;
        src->image_pre = image_pre;
        if (filter_type & NLMEANS_PREFILTER_MODE_PASSTHRU)
        {
            src->mem   = src->mem_pre;
            src->image = src->image_pre;
        }

    }
    src->prefiltered = 1;
    hb_unlock(src->mutex);
}