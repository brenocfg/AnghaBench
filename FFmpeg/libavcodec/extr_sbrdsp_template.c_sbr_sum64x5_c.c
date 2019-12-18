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
typedef  scalar_t__ INTFLOAT ;

/* Variables and functions */

__attribute__((used)) static void sbr_sum64x5_c(INTFLOAT *z)
{
    int k;
    for (k = 0; k < 64; k++) {
        INTFLOAT f = z[k] + z[k + 64] + z[k + 128] + z[k + 192] + z[k + 256];
        z[k] = f;
    }
}