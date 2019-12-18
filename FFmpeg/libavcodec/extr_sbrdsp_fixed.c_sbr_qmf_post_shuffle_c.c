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

__attribute__((used)) static void sbr_qmf_post_shuffle_c(int W[32][2], const int *z)
{
    int k;
    for (k = 0; k < 32; k++) {
        W[k][0] = -z[63-k];
        W[k][1] = z[k];
    }
}