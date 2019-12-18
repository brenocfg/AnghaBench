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
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int APESIGN (int) ; 

__attribute__((used)) static void long_filter_ehigh_3830(int32_t *buffer, int length)
{
    int i, j;
    int32_t dotprod, sign;
    int32_t delay[8] = { 0 };
    uint32_t coeffs[8] = { 0 };

    for (i = 0; i < length; i++) {
        dotprod = 0;
        sign = APESIGN(buffer[i]);
        for (j = 7; j >= 0; j--) {
            dotprod += delay[j] * coeffs[j];
            coeffs[j] += ((delay[j] >> 31) | 1) * sign;
        }
        for (j = 7; j > 0; j--)
            delay[j] = delay[j - 1];
        delay[0] = buffer[i];
        buffer[i] -= dotprod >> 9;
    }
}