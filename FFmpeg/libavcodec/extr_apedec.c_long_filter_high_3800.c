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
typedef  unsigned int int32_t ;

/* Variables and functions */
 unsigned int APESIGN (unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void long_filter_high_3800(int32_t *buffer, int order, int shift, int length)
{
    int i, j;
    int32_t dotprod, sign;
    int32_t coeffs[256], delay[256];

    if (order >= length)
        return;

    memset(coeffs, 0, order * sizeof(*coeffs));
    for (i = 0; i < order; i++)
        delay[i] = buffer[i];
    for (i = order; i < length; i++) {
        dotprod = 0;
        sign = APESIGN(buffer[i]);
        for (j = 0; j < order; j++) {
            dotprod += delay[j] * (unsigned)coeffs[j];
            coeffs[j] += ((delay[j] >> 31) | 1) * sign;
        }
        buffer[i] -= dotprod >> shift;
        for (j = 0; j < order - 1; j++)
            delay[j] = delay[j + 1];
        delay[order - 1] = buffer[i];
    }
}