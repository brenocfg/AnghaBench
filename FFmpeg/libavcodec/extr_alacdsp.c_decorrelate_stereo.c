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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static void decorrelate_stereo(int32_t *buffer[2], int nb_samples,
                               int decorr_shift, int decorr_left_weight)
{
    int i;

    for (i = 0; i < nb_samples; i++) {
        int32_t a, b;

        a = buffer[0][i];
        b = buffer[1][i];

        a -= (b * decorr_left_weight) >> decorr_shift;
        b += a;

        buffer[0][i] = b;
        buffer[1][i] = a;
    }
}