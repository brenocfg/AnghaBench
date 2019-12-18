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
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void ac3_downmix_5_to_1_symmetric_c_fixed(int32_t **samples, int16_t **matrix,
                                                 int len)
{
    int i;
    int64_t v0;
    int16_t front_mix    = matrix[0][0];
    int16_t center_mix   = matrix[0][1];
    int16_t surround_mix = matrix[0][3];

    for (i = 0; i < len; i++) {
        v0 = (int64_t)samples[0][i] * front_mix    +
             (int64_t)samples[1][i] * center_mix   +
             (int64_t)samples[2][i] * front_mix    +
             (int64_t)samples[3][i] * surround_mix +
             (int64_t)samples[4][i] * surround_mix;

        samples[0][i] = (v0+2048)>>12;
    }
}