#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int dwLength; scalar_t__ dwAvailPhys; } ;
struct TYPE_5__ {int dwLength; scalar_t__ ullAvailPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;
typedef  TYPE_2__ MEMORYSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMemoryStatus (TYPE_2__*) ; 
 int /*<<< orphan*/  GlobalMemoryStatusEx (TYPE_1__*) ; 
 scalar_t__ frontend_uwp_get_mem_total () ; 

__attribute__((used)) static uint64_t frontend_uwp_get_mem_used(void)
{
   /* OSes below 2000 don't have the Ex version,
    * and non-Ex cannot work with >4GB RAM */
#if _WIN32_WINNT >= 0x0500
   MEMORYSTATUSEX mem_info;
   mem_info.dwLength = sizeof(MEMORYSTATUSEX);
   GlobalMemoryStatusEx(&mem_info);
   return ((frontend_uwp_get_mem_total() - mem_info.ullAvailPhys));
#else
   MEMORYSTATUS mem_info;
   mem_info.dwLength = sizeof(MEMORYSTATUS);
   GlobalMemoryStatus(&mem_info);
   return ((frontend_uwp_get_mem_total() - mem_info.dwAvailPhys));
#endif
}