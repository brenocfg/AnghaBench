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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int PITCH_MAX ; 
 int PITCH_ORDER ; 
 int SUBFRAME_LEN ; 

void ff_g723_1_get_residual(int16_t *residual, int16_t *prev_excitation,
                            int lag)
{
    int offset = PITCH_MAX - PITCH_ORDER / 2 - lag;
    int i;

    residual[0] = prev_excitation[offset];
    residual[1] = prev_excitation[offset + 1];

    offset += 2;
    for (i = 2; i < SUBFRAME_LEN + PITCH_ORDER - 1; i++)
        residual[i] = prev_excitation[offset + (i - 2) % lag];
}