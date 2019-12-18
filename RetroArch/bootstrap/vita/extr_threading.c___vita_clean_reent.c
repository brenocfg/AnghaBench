#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int needs_reclaim; scalar_t__ thread_id; } ;
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ SceKernelThreadInfo ;

/* Variables and functions */
 int MAX_THREADS ; 
 TYPE_3__* reent_list ; 
 scalar_t__ sceKernelGetThreadInfo (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static inline void __vita_clean_reent(void)
{
	int i;
	SceKernelThreadInfo info;

	for (i = 0; i < MAX_THREADS; ++i)
	{
		info.size = sizeof(SceKernelThreadInfo);

		if (sceKernelGetThreadInfo(reent_list[i].thread_id, &info) < 0)
		{
			reent_list[i].thread_id = 0;
			reent_list[i].needs_reclaim = 1;
		}
	}
}