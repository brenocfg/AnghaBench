#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_5__ {TYPE_1__* avctx; } ;
struct TYPE_4__ {int nsse_weight; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FFABS (int) ; 

__attribute__((used)) static int nsse16_c(MpegEncContext *c, uint8_t *s1, uint8_t *s2,
                    ptrdiff_t stride, int h)
{
    int score1 = 0, score2 = 0, x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < 16; x++)
            score1 += (s1[x] - s2[x]) * (s1[x] - s2[x]);
        if (y + 1 < h) {
            for (x = 0; x < 15; x++)
                score2 += FFABS(s1[x]     - s1[x + stride] -
                                s1[x + 1] + s1[x + stride + 1]) -
                          FFABS(s2[x]     - s2[x + stride] -
                                s2[x + 1] + s2[x + stride + 1]);
        }
        s1 += stride;
        s2 += stride;
    }

    if (c)
        return score1 + FFABS(score2) * c->avctx->nsse_weight;
    else
        return score1 + FFABS(score2) * 8;
}