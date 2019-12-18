#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sign; int exp; int mant; } ;
typedef  TYPE_1__ Float11 ;

/* Variables and functions */
 int av_log2_16bit (int) ; 

__attribute__((used)) static inline Float11* i2f(int i, Float11* f)
{
    f->sign = (i < 0);
    if (f->sign)
        i = -i;
    f->exp = av_log2_16bit(i) + !!i;
    f->mant = i? (i<<6) >> f->exp : 1<<5;
    return f;
}