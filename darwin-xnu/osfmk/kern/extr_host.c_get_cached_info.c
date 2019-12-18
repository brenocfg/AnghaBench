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
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/  host_info64_t ;
struct TYPE_2__ {int count; scalar_t__ data; } ;

/* Variables and functions */
 int NUM_HOST_INFO_DATA_TYPES ; 
 TYPE_1__* g_host_stats_cache ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
get_cached_info(int index, host_info64_t info, mach_msg_type_number_t* count)
{
    if (index < 0 || index >= NUM_HOST_INFO_DATA_TYPES) {
        *count = 0;
        return;
    }

    *count = g_host_stats_cache[index].count;
    memcpy(info, (void *)g_host_stats_cache[index].data, g_host_stats_cache[index].count * sizeof(integer_t));
}