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
typedef  int uint64_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_clipl_int32 (int) ; 
 int av_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_optimal_param(uint64_t sum, int n, int max_param)
{
    int k;
    uint64_t sum2;

    if (sum <= n >> 1)
        return 0;
    sum2 = sum - (n >> 1);
    k    = av_log2(av_clipl_int32(sum2 / n));
    return FFMIN(k, max_param);
}