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
struct zcc_magazine {int dummy; } ;

/* Variables and functions */

void zcache_swap_magazines(struct zcc_magazine **a, struct zcc_magazine **b)
{
	struct zcc_magazine *temp = *a;
	*a = *b;
	*b = temp;
}