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
typedef  size_t ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* sub_median_pred ) (int*,int*,int*,int,int*,int*) ;} ;
struct TYPE_5__ {TYPE_1__ llvidencdsp; } ;
typedef  TYPE_2__ MagicYUVContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int*,int*,int*,int,int*,int*) ; 

__attribute__((used)) static void median_predict(MagicYUVContext *s,
                           uint8_t *src, uint8_t *dst, ptrdiff_t stride,
                           int width, int height)
{
    int left = 0, lefttop;
    int i, j;

    for (i = 0; i < width; i++) {
        dst[i] = src[i] - left;
        left   = src[i];
    }
    dst += width;
    src += stride;
    for (j = 1; j < height; j++) {
        left = lefttop = src[-stride];
        s->llvidencdsp.sub_median_pred(dst, src - stride, src, width, &left, &lefttop);
        dst += width;
        src += stride;
    }
}