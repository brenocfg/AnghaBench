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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 size_t av_clip_uint8 (unsigned int) ; 
 int /*<<< orphan*/  compute_contrast_change (float*,float*,unsigned int*,size_t) ; 
 int /*<<< orphan*/  compute_histogram8 (size_t const*,int /*<<< orphan*/ ,int,int,float*,size_t) ; 

__attribute__((used)) static void midequalizer8(const uint8_t *in0, const uint8_t *in1,
                          uint8_t *dst,
                          ptrdiff_t linesize1, ptrdiff_t linesize2,
                          ptrdiff_t dlinesize,
                          int w0, int h0,
                          int w1, int h1,
                          float *histogram1, float *histogram2,
                          unsigned *cchange,
                          size_t hsize)
{
    int x, y;

    compute_histogram8(in0, linesize1, w0, h0, histogram1, hsize);
    compute_histogram8(in1, linesize2, w1, h1, histogram2, hsize);

    compute_contrast_change(histogram1, histogram2, cchange, hsize);

    for (y = 0; y < h0; y++) {
        for (x = 0; x < w0; x++) {
            dst[x] = av_clip_uint8(cchange[in0[x]]);
        }
        dst += dlinesize;
        in0 += linesize1;
    }
}