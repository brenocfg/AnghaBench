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
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* sub_median_pred ) (int*,int*,int*,int,int*,int*) ;} ;
struct TYPE_5__ {TYPE_1__ llvidencdsp; } ;
typedef  TYPE_2__ UtvideoContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int*,int*,int*,int,int*,int*) ; 

__attribute__((used)) static void median_predict(UtvideoContext *c, uint8_t *src, uint8_t *dst,
                           ptrdiff_t stride, int width, int height)
{
    int i, j;
    int A, B;
    uint8_t prev;

    /* First line uses left neighbour prediction */
    prev = 0x80; /* Set the initial value */
    for (i = 0; i < width; i++) {
        *dst++ = src[i] - prev;
        prev   = src[i];
    }

    if (height == 1)
        return;

    src += stride;

    /*
     * Second line uses top prediction for the first sample,
     * and median for the rest.
     */
    A = B = 0;

    /* Rest of the coded part uses median prediction */
    for (j = 1; j < height; j++) {
        c->llvidencdsp.sub_median_pred(dst, src - stride, src, width, &A, &B);
        dst += width;
        src += stride;
    }
}