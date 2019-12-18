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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  MpegEncContext ;

/* Variables and functions */
 scalar_t__ V (int) ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__ mid_pred (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int pix_median_abs16_c(MpegEncContext *v, uint8_t *pix1, uint8_t *pix2,
                             ptrdiff_t stride, int h)
{
    int s = 0, i, j;

#define V(x) (pix1[x] - pix2[x])

    s    += abs(V(0));
    s    += abs(V(1) - V(0));
    s    += abs(V(2) - V(1));
    s    += abs(V(3) - V(2));
    s    += abs(V(4) - V(3));
    s    += abs(V(5) - V(4));
    s    += abs(V(6) - V(5));
    s    += abs(V(7) - V(6));
    s    += abs(V(8) - V(7));
    s    += abs(V(9) - V(8));
    s    += abs(V(10) - V(9));
    s    += abs(V(11) - V(10));
    s    += abs(V(12) - V(11));
    s    += abs(V(13) - V(12));
    s    += abs(V(14) - V(13));
    s    += abs(V(15) - V(14));

    pix1 += stride;
    pix2 += stride;

    for (i = 1; i < h; i++) {
        s    += abs(V(0) - V(-stride));
        for (j = 1; j < 16; j++)
            s    += abs(V(j) - mid_pred(V(j-stride), V(j-1), V(j-stride) + V(j-1) - V(j-stride-1)));
        pix1 += stride;
        pix2 += stride;

    }
#undef V
    return s;
}