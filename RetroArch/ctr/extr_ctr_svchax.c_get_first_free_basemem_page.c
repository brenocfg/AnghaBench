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
typedef  int u32 ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  MEMREGION_BASE ; 
 scalar_t__ SYSTEM_VERSION (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ osGetKernelVersion () ; 
 int osGetMemRegionUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcGetSystemInfo (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_first_free_basemem_page(bool isNew3DS)
{
   s64 v1;
   int memused_base;
   int memused_base_linear;  // guessed

   memused_base = osGetMemRegionUsed(MEMREGION_BASE);

   svcGetSystemInfo(&v1, 2, 0);
   memused_base_linear = 0x6C000 + v1 +
                         (osGetKernelVersion() > SYSTEM_VERSION(2, 49, 0) ? (isNew3DS ? 0x2000 : 0x1000) : 0x0);

   return (osGetKernelVersion() > SYSTEM_VERSION(2, 40, 0) ? 0xE0000000 : 0xF0000000) // kernel FCRAM mapping
          + (isNew3DS ? 0x10000000 : 0x08000000)  // FCRAM size
          - (memused_base - memused_base_linear)  // memory usage for pages allocated without the MEMOP_LINEAR flag
          - 0x1000;  // skip to the start addr of the next free page

}