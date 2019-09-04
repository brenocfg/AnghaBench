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
typedef  scalar_t__ int8_t ;

/* Variables and functions */

__attribute__((used)) static int restore_weight(int8_t weight)
{
    int result;

    if ((result = (int) weight << 3) > 0)
        result += (result + 64) >> 7;

    return result;
}