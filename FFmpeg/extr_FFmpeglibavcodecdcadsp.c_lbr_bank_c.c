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
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void lbr_bank_c(float output[32][4], float **input,
                       const float *coeff, ptrdiff_t ofs, ptrdiff_t len)
{
    float SW0 = coeff[0];
    float SW1 = coeff[1];
    float SW2 = coeff[2];
    float SW3 = coeff[3];

    float C1  = coeff[4];
    float C2  = coeff[5];
    float C3  = coeff[6];
    float C4  = coeff[7];

    float AL1 = coeff[8];
    float AL2 = coeff[9];

    int i;

    // Short window and 8 point forward MDCT
    for (i = 0; i < len; i++) {
        float *src = input[i] + ofs;

        float a = src[-4] * SW0 - src[-1] * SW3;
        float b = src[-3] * SW1 - src[-2] * SW2;
        float c = src[ 2] * SW1 + src[ 1] * SW2;
        float d = src[ 3] * SW0 + src[ 0] * SW3;

        output[i][0] = C1 * b - C2 * c + C4 * a - C3 * d;
        output[i][1] = C1 * d - C2 * a - C4 * b - C3 * c;
        output[i][2] = C3 * b + C2 * d - C4 * c + C1 * a;
        output[i][3] = C3 * a - C2 * b + C4 * d - C1 * c;
    }

    // Aliasing cancellation for high frequencies
    for (i = 12; i < len - 1; i++) {
        float a = output[i  ][3] * AL1;
        float b = output[i+1][0] * AL1;
        output[i  ][3] += b - a;
        output[i+1][0] -= b + a;
        a = output[i  ][2] * AL2;
        b = output[i+1][1] * AL2;
        output[i  ][2] += b - a;
        output[i+1][1] -= b + a;
    }
}