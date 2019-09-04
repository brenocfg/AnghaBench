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
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int SUBFRAME_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

void ff_g723_1_gen_dirac_train(int16_t *buf, int pitch_lag)
{
    int16_t vector[SUBFRAME_LEN];
    int i, j;

    memcpy(vector, buf, SUBFRAME_LEN * sizeof(*vector));
    for (i = pitch_lag; i < SUBFRAME_LEN; i += pitch_lag) {
        for (j = 0; j < SUBFRAME_LEN - i; j++)
            buf[i + j] += vector[j];
    }
}