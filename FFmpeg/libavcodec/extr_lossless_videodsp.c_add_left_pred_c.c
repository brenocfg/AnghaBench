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
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static int add_left_pred_c(uint8_t *dst, const uint8_t *src, ptrdiff_t w,
                           int acc)
{
    int i;

    for (i = 0; i < w - 1; i++) {
        acc   += src[i];
        dst[i] = acc;
        i++;
        acc   += src[i];
        dst[i] = acc;
    }

    for (; i < w; i++) {
        acc   += src[i];
        dst[i] = acc;
    }

    return acc;
}