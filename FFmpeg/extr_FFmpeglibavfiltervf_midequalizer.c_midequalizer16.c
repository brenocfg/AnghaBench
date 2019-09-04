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
typedef  size_t uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  compute_contrast_change (float*,float*,unsigned int*,size_t) ; 
 int /*<<< orphan*/  compute_histogram16 (size_t const*,int,int,int,float*,size_t) ; 

__attribute__((used)) static void midequalizer16(const uint8_t *in0, const uint8_t *in1,
                           uint8_t *dst,
                           ptrdiff_t linesize1, ptrdiff_t linesize2,
                           ptrdiff_t dlinesize,
                           int w0, int h0,
                           int w1, int h1,
                           float *histogram1, float *histogram2,
                           unsigned *cchange,
                           size_t hsize)
{
    const uint16_t *i = (const uint16_t *)in0;
    uint16_t *d = (uint16_t *)dst;
    int x, y;

    compute_histogram16(i, linesize1 / 2, w0, h0, histogram1, hsize);
    compute_histogram16((const uint16_t *)in1, linesize2 / 2, w1, h1, histogram2, hsize);

    compute_contrast_change(histogram1, histogram2, cchange, hsize);

    for (y = 0; y < h0; y++) {
        for (x = 0; x < w0; x++) {
            d[x] = cchange[i[x]];
        }
        d += dlinesize / 2;
        i += linesize1 / 2;
    }
}