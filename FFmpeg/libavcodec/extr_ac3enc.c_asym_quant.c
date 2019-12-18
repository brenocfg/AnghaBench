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

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static inline int asym_quant(int c, int e, int qbits)
{
    int m;

    c = (((c * (1<<e)) >> (24 - qbits)) + 1) >> 1;
    m = (1 << (qbits-1));
    if (c >= m)
        c = m - 1;
    av_assert2(c >= -m);
    return c;
}