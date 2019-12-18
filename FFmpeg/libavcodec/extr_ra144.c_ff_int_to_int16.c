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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int LPC_ORDER ; 

void ff_int_to_int16(int16_t *out, const int *inp)
{
    int i;

    for (i = 0; i < LPC_ORDER; i++)
        *out++ = *inp++;
}