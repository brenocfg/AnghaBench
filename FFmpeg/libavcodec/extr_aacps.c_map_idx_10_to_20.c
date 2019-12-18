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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */

__attribute__((used)) static void map_idx_10_to_20(int8_t *par_mapped, const int8_t *par, int full)
{
    int b;
    if (full)
        b = 9;
    else {
        b = 4;
        par_mapped[10] = 0;
    }
    for (; b >= 0; b--) {
        par_mapped[2*b+1] = par_mapped[2*b] = par[b];
    }
}