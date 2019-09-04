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
typedef  int SUINT ;

/* Variables and functions */
 int* table_4_3_exp ; 
 unsigned int* table_4_3_value ; 

__attribute__((used)) static inline int l3_unscale(int value, int exponent)
{
    unsigned int m;
    int e;

    e  = table_4_3_exp  [4 * value + (exponent & 3)];
    m  = table_4_3_value[4 * value + (exponent & 3)];
    e -= exponent >> 2;
#ifdef DEBUG
    if(e < 1)
        av_log(NULL, AV_LOG_WARNING, "l3_unscale: e is %d\n", e);
#endif
    if (e > (SUINT)31)
        return 0;
    m = (m + ((1U << e)>>1)) >> e;

    return m;
}