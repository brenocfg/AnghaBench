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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static int32_t scalarproduct_int16_c(const int16_t * v1, const int16_t * v2, int order)
{
    int res = 0;

    while (order--)
        res += *v1++ * *v2++;

    return res;
}