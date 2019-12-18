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
typedef  int int64_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int INT64_C (int) ; 
 scalar_t__ av_clip_int16 (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,unsigned int) ; 

__attribute__((used)) static void filterfn(int16_t *dest, int16_t *tmp, unsigned size, int64_t scale)
{
    int16_t *low, *high, *ll, *lh, *hl, *hh;
    int hsize, i, j;
    int64_t value;

    hsize = size >> 1;
    low   = tmp + 4;
    high  = &low[hsize + 8];

    memcpy(low, dest, size);
    memcpy(high, dest + hsize, size);

    ll = &low[hsize];
    lh = &low[hsize];
    hl = &high[hsize];
    hh = hl;
    for (i = 4, j = 2; i; i--, j++, ll--, hh++, lh++, hl--) {
        low[i - 5]  = low[j - 1];
        lh[0]       = ll[-1];
        high[i - 5] = high[j - 2];
        hh[0]       = hl[-2];
    }

    for (i = 0; i < hsize; i++) {
        value = (int64_t) low [i + 1] * -INT64_C(325392907)  +
                (int64_t) low [i + 0] *  INT64_C(3687786320) +
                (int64_t) low [i - 1] * -INT64_C(325392907)  +
                (int64_t) high[i + 0] *  INT64_C(1518500249) +
                (int64_t) high[i - 1] *  INT64_C(1518500249);
        dest[i * 2] = av_clip_int16(((value >> 32) * scale) >> 32);
    }

    for (i = 0; i < hsize; i++) {
        value = (int64_t) low [i + 2] * -INT64_C(65078576)   +
                (int64_t) low [i + 1] *  INT64_C(1583578880) +
                (int64_t) low [i + 0] *  INT64_C(1583578880) +
                (int64_t) low [i - 1] * -INT64_C(65078576)   +
                (int64_t) high[i + 1] *  INT64_C(303700064)  +
                (int64_t) high[i + 0] * -INT64_C(3644400640) +
                (int64_t) high[i - 1] *  INT64_C(303700064);
        dest[i * 2 + 1] = av_clip_int16(((value >> 32) * scale) >> 32);
    }
}