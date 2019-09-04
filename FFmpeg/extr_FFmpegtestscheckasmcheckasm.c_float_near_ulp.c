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
union av_intfloat32 {float f; scalar_t__ i; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ is_negative (union av_intfloat32) ; 
 unsigned int llabs (scalar_t__) ; 

int float_near_ulp(float a, float b, unsigned max_ulp)
{
    union av_intfloat32 x, y;

    x.f = a;
    y.f = b;

    if (is_negative(x) != is_negative(y)) {
        // handle -0.0 == +0.0
        return a == b;
    }

    if (llabs((int64_t)x.i - y.i) <= max_ulp)
        return 1;

    return 0;
}