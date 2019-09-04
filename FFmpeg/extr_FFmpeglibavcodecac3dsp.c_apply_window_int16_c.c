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
typedef  int int16_t ;

/* Variables and functions */
 int MUL16 (int const,int) ; 

__attribute__((used)) static void apply_window_int16_c(int16_t *output, const int16_t *input,
                                 const int16_t *window, unsigned int len)
{
    int i;
    int len2 = len >> 1;

    for (i = 0; i < len2; i++) {
        int16_t w       = window[i];
        output[i]       = (MUL16(input[i],       w) + (1 << 14)) >> 15;
        output[len-i-1] = (MUL16(input[len-i-1], w) + (1 << 14)) >> 15;
    }
}