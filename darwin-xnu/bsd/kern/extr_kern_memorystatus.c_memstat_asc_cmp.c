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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ msi_page_count; } ;
typedef  TYPE_1__ memstat_sort_info_t ;

/* Variables and functions */

__attribute__((used)) static int memstat_asc_cmp(const void *a, const void *b)
{
        const memstat_sort_info_t *msA = (const memstat_sort_info_t *)a;
        const memstat_sort_info_t *msB = (const memstat_sort_info_t *)b;

        return (int)((uint64_t)msA->msi_page_count - (uint64_t)msB->msi_page_count);
}