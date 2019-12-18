#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/  host_info64_t ;
struct TYPE_5__ {int count; scalar_t__ data; } ;
struct TYPE_4__ {int t_flags; } ;

/* Variables and functions */
 int NUM_HOST_INFO_DATA_TYPES ; 
 int TF_PLATFORM ; 
 TYPE_1__* current_task () ; 
 TYPE_2__* g_host_stats_cache ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cache_host_statistics(int index, host_info64_t info)
{
    if (index < 0 || index >= NUM_HOST_INFO_DATA_TYPES)
        return;

    task_t task = current_task();
    if (task->t_flags & TF_PLATFORM)
        return;

    memcpy((void *)g_host_stats_cache[index].data, info, g_host_stats_cache[index].count * sizeof(integer_t));
    return;
}