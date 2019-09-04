#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16_t ;
struct TYPE_16__ {int* v; } ;
typedef  TYPE_1__ AVInteger ;

/* Variables and functions */
 int AV_INTEGER_SIZE ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 scalar_t__ av_cmp_i (TYPE_1__,TYPE_1__) ; 
 scalar_t__ av_log2_i (TYPE_1__) ; 
 TYPE_1__ av_shr_i (TYPE_1__,int) ; 
 TYPE_1__ av_sub_i (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ zero_i ; 

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    int i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    if(!quot) quot = &quot_temp;

    if ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        return av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    if(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, sizeof(AVInteger));

    while(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        if(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    return a;
}