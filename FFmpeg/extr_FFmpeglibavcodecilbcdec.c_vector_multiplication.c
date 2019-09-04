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

__attribute__((used)) static void vector_multiplication(int16_t *out, const int16_t *in,
                                  const int16_t *win, int length,
                                  int shift)
{
    for (int i = 0; i < length; i++)
        out[i] = (in[i] * win[i]) >> shift;
}