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
struct SwsContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sws_scale (struct SwsContext*,int const* const*,int*,int /*<<< orphan*/ ,int const,int**,int*) ; 

__attribute__((used)) static void blur(uint8_t       *dst, const int dst_linesize,
                 const uint8_t *src, const int src_linesize,
                 const int w, const int h, const int threshold,
                 struct SwsContext *filter_context)
{
    int x, y;
    int orig, filtered;
    int diff;
    /* Declare arrays of 4 to get aligned data */
    const uint8_t* const src_array[4] = {src};
    uint8_t *dst_array[4]             = {dst};
    int src_linesize_array[4] = {src_linesize};
    int dst_linesize_array[4] = {dst_linesize};

    sws_scale(filter_context, src_array, src_linesize_array,
              0, h, dst_array, dst_linesize_array);

    if (threshold > 0) {
        for (y = 0; y < h; ++y) {
            for (x = 0; x < w; ++x) {
                orig     = src[x + y * src_linesize];
                filtered = dst[x + y * dst_linesize];
                diff     = orig - filtered;

                if (diff > 0) {
                    if (diff > 2 * threshold)
                        dst[x + y * dst_linesize] = orig;
                    else if (diff > threshold)
                        /* add 'diff' and subtract 'threshold' from 'filtered' */
                        dst[x + y * dst_linesize] = orig - threshold;
                } else {
                    if (-diff > 2 * threshold)
                        dst[x + y * dst_linesize] = orig;
                    else if (-diff > threshold)
                        /* add 'diff' and 'threshold' to 'filtered' */
                        dst[x + y * dst_linesize] = orig + threshold;
                }
            }
        }
    } else if (threshold < 0) {
        for (y = 0; y < h; ++y) {
            for (x = 0; x < w; ++x) {
                orig     = src[x + y * src_linesize];
                filtered = dst[x + y * dst_linesize];
                diff     = orig - filtered;

                if (diff > 0) {
                    if (diff <= -threshold)
                        dst[x + y * dst_linesize] = orig;
                    else if (diff <= -2 * threshold)
                        /* subtract 'diff' and 'threshold' from 'orig' */
                        dst[x + y * dst_linesize] = filtered - threshold;
                } else {
                    if (diff >= threshold)
                        dst[x + y * dst_linesize] = orig;
                    else if (diff >= 2 * threshold)
                        /* add 'threshold' and subtract 'diff' from 'orig' */
                        dst[x + y * dst_linesize] = filtered + threshold;
                }
            }
        }
    }
}