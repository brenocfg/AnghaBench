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
 int mid_pred (int,int,int) ; 

__attribute__((used)) static void add_lag_median_prediction(uint8_t *dst, uint8_t *src1,
                                      uint8_t *diff, int w, int *left,
                                      int *left_top)
{
    /* This is almost identical to add_hfyu_median_pred in huffyuvdsp.h.
     * However the &0xFF on the gradient predictor yields incorrect output
     * for lagarith.
     */
    int i;
    uint8_t l, lt;

    l  = *left;
    lt = *left_top;

    for (i = 0; i < w; i++) {
        l = mid_pred(l, src1[i], l + src1[i] - lt) + diff[i];
        lt = src1[i];
        dst[i] = l;
    }

    *left     = l;
    *left_top = lt;
}