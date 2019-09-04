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
typedef  int ptrdiff_t ;

/* Variables and functions */
 float SQR (float const) ; 

__attribute__((used)) static void compute_cache_c(float *cache, const float *f,
                            ptrdiff_t S, ptrdiff_t K,
                            ptrdiff_t i, ptrdiff_t jj)
{
    int v = 0;

    for (int j = jj; j < jj + S; j++, v++)
        cache[v] += -SQR(f[i - K - 1] - f[j - K - 1]) + SQR(f[i + K] - f[j + K]);
}