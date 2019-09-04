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
typedef  int /*<<< orphan*/  VagueDenoiserContext ;

/* Variables and functions */
 int NPAD ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int const) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  symmetric_extension (float*,int const,int,int) ; 
 float* synthesis_high ; 
 float* synthesis_low ; 

__attribute__((used)) static void invert_step(const float *input, float *output, float *temp, const int size, VagueDenoiserContext *s)
{
    const int low_size = (size + 1) >> 1;
    const int high_size = size >> 1;
    int left_ext = 1, right_ext, i;
    int findex;

    memcpy(temp + NPAD, input + NPAD, low_size * sizeof(float));

    right_ext = (size % 2 == 0) ? 2 : 1;
    symmetric_extension(temp, low_size, left_ext, right_ext);

    memset(output, 0, (NPAD + NPAD + size) * sizeof(float));
    findex = (size + 2) >> 1;

    for (i = 9; i < findex + 11; i++) {
        const float a = temp[i] * synthesis_low[0];
        const float b = temp[i] * synthesis_low[1];
        const float c = temp[i] * synthesis_low[2];
        const float d = temp[i] * synthesis_low[3];

        output[2 * i - 13] += a;
        output[2 * i - 12] += b;
        output[2 * i - 11] += c;
        output[2 * i - 10] += d;
        output[2 * i -  9] += c;
        output[2 * i -  8] += b;
        output[2 * i -  7] += a;
    }

    memcpy(temp + NPAD, input + NPAD + low_size, high_size * sizeof(float));

    left_ext = 2;
    right_ext = (size % 2 == 0) ? 1 : 2;
    symmetric_extension(temp, high_size, left_ext, right_ext);

    for (i = 8; i < findex + 11; i++) {
        const float a = temp[i] * synthesis_high[0];
        const float b = temp[i] * synthesis_high[1];
        const float c = temp[i] * synthesis_high[2];
        const float d = temp[i] * synthesis_high[3];
        const float e = temp[i] * synthesis_high[4];

        output[2 * i - 13] += a;
        output[2 * i - 12] += b;
        output[2 * i - 11] += c;
        output[2 * i - 10] += d;
        output[2 * i -  9] += e;
        output[2 * i -  8] += d;
        output[2 * i -  7] += c;
        output[2 * i -  6] += b;
        output[2 * i -  5] += a;
    }
}