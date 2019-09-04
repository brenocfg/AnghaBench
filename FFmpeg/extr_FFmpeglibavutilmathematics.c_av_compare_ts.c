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
typedef  int int64_t ;
struct TYPE_4__ {int num; scalar_t__ den; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int FFABS (int) ; 
 int INT_MAX ; 
 int av_rescale_rnd (int,int,int,int /*<<< orphan*/ ) ; 

int av_compare_ts(int64_t ts_a, AVRational tb_a, int64_t ts_b, AVRational tb_b)
{
    int64_t a = tb_a.num * (int64_t)tb_b.den;
    int64_t b = tb_b.num * (int64_t)tb_a.den;
    if ((FFABS(ts_a)|a|FFABS(ts_b)|b) <= INT_MAX)
        return (ts_a*a > ts_b*b) - (ts_a*a < ts_b*b);
    if (av_rescale_rnd(ts_a, a, b, AV_ROUND_DOWN) < ts_b)
        return -1;
    if (av_rescale_rnd(ts_b, b, a, AV_ROUND_DOWN) < ts_a)
        return 1;
    return 0;
}