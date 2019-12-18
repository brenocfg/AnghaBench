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
typedef  int uint8_t ;
typedef  size_t ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void predictor_scalar(uint8_t *src, ptrdiff_t size)
{
    ptrdiff_t i;

    for (i = 1; i < size; i++)
        src[i] += src[i-1] - 128;
}