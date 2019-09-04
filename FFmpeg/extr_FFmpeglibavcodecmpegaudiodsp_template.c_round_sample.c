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
typedef  int int64_t ;

/* Variables and functions */
 int OUT_SHIFT ; 
 int av_clip_int16 (int) ; 

__attribute__((used)) static inline int round_sample(int64_t *sum)
{
    int sum1;
    sum1 = (int)((*sum) >> OUT_SHIFT);
    *sum &= (1<<OUT_SHIFT)-1;
    return av_clip_int16(sum1);
}