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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 scalar_t__ MUL16 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

int64_t ff_dot_product(const int16_t *a, const int16_t *b, int length)
{
    int i;
    int64_t sum = 0;

    for (i = 0; i < length; i++)
        sum += MUL16(a[i], b[i]);

    return sum;
}