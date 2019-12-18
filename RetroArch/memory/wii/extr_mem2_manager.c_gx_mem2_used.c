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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  used_size; } ;
typedef  TYPE_1__ heap_iblock ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_heap_getinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gx_mem2_heap ; 

uint32_t gx_mem2_used(void)
{
   heap_iblock info;
   __lwp_heap_getinfo(&gx_mem2_heap, &info);
   return info.used_size;
}