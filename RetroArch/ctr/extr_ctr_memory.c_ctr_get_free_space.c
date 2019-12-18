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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  svcGetSystemInfo (scalar_t__*,int /*<<< orphan*/ ,int) ; 

u32 ctr_get_free_space(void)
{
   s64 mem_used;
   u32 app_memory = *((u32*)0x1FF80040);
   svcGetSystemInfo(&mem_used, 0, 1);
   return app_memory - (u32)mem_used;
}