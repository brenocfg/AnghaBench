#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* tap; int normalize; } ;
typedef  TYPE_1__ filter_param_t ;

/* Variables and functions */
 int* hb_crop_table ; 

__attribute__((used)) static inline int blend_filter_pixel(filter_param_t *filter, int up2, int up1, int current, int down1, int down2)
{
    /* Low-pass 5-tap filter */
    int result = 0;

    result += up2 * filter->tap[0];
    result += up1 * filter->tap[1];
    result += current * filter->tap[2];
    result += down1 * filter->tap[3];
    result += down2 * filter->tap[4];
    result >>= filter->normalize;

    result = hb_crop_table[result + 1024];
    return result;
}