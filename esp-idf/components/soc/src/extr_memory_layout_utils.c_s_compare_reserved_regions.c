#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ start; } ;
typedef  TYPE_1__ soc_reserved_region_t ;

/* Variables and functions */

__attribute__((used)) static int s_compare_reserved_regions(const void *a, const void *b)
{
    const soc_reserved_region_t *r_a = (soc_reserved_region_t *)a;
    const soc_reserved_region_t *r_b = (soc_reserved_region_t *)b;
    return (int)r_a->start - (int)r_b->start;
}