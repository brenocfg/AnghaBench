#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int address; int size; struct TYPE_3__* next; } ;
typedef  TYPE_1__ s_mem_area ;

/* Variables and functions */
 TYPE_1__* MEM_AREA_TABLE ; 

__attribute__((used)) static inline void memoryAddArea(int start, int end, int cur_index)
{
    /* Create and copy new memory area */
    s_mem_area * mem_area = MEM_AREA_TABLE;
    mem_area[cur_index].address = start;
    mem_area[cur_index].size    = end - start;
    mem_area[cur_index].next    = 0;

    /* Fill pointer to this area in the previous area */
    if (cur_index > 0)
    {
        mem_area[cur_index - 1].next = &mem_area[cur_index];
    }
}