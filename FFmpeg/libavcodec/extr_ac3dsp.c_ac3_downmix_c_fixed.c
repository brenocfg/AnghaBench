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

__attribute__((used)) static void ac3_downmix_c_fixed(int32_t **samples, int16_t **matrix,
                                int out_ch, int in_ch, int len)
{
    int i, j;
    int64_t v0, v1;
    if (out_ch == 2) {
        for (i = 0; i < len; i++) {
            v0 = v1 = 0;
            for (j = 0; j < in_ch; j++) {
                v0 += (int64_t)samples[j][i] * matrix[0][j];
                v1 += (int64_t)samples[j][i] * matrix[1][j];
            }
            samples[0][i] = (v0+2048)>>12;
            samples[1][i] = (v1+2048)>>12;
        }
    } else if (out_ch == 1) {
        for (i = 0; i < len; i++) {
            v0 = 0;
            for (j = 0; j < in_ch; j++)
                v0 += (int64_t)samples[j][i] * matrix[0][j];
            samples[0][i] = (v0+2048)>>12;
        }
    }
}