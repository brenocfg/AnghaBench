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

/* Variables and functions */

__attribute__((used)) static void sum_b(const int *input, int *output, int len)
{
    int i;

    output[0] = input[0];
    for (i = 1; i < len; i++)
        output[i] = input[2 * i] + input[2 * i - 1];
}