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
typedef  int uint32_t ;

/* Variables and functions */
 int CELT_PVQ_U (int,int) ; 
 int FFABS (int const) ; 

__attribute__((used)) static inline uint32_t celt_icwrsi(uint32_t N, uint32_t K, const int *y)
{
    int i, idx = 0, sum = 0;
    for (i = N - 1; i >= 0; i--) {
        const uint32_t i_s = CELT_PVQ_U(N - i, sum + FFABS(y[i]) + 1);
        idx += CELT_PVQ_U(N - i, sum) + (y[i] < 0)*i_s;
        sum += FFABS(y[i]);
    }
    return idx;
}