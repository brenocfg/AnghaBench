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
union av_intfloat32 {float f; int i; } ;

/* Variables and functions */

__attribute__((used)) static inline float flt16_even(float pf)
{
    union av_intfloat32 tmp;
    tmp.f = pf;
    tmp.i = (tmp.i + 0x00007FFFU + (tmp.i & 0x00010000U >> 16)) & 0xFFFF0000U;
    return tmp.f;
}