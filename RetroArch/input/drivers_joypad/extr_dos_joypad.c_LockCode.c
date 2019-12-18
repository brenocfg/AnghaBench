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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int size; scalar_t__ address; scalar_t__ handle; } ;
typedef  TYPE_1__ __dpmi_meminfo ;

/* Variables and functions */
 int __dpmi_get_segment_base_address (int /*<<< orphan*/ ,scalar_t__*) ; 
 int __dpmi_lock_linear_region (TYPE_1__*) ; 
 int /*<<< orphan*/  _my_cs () ; 

int LockCode(void *a, int size)
{
   uint32_t baseaddr;
   __dpmi_meminfo region;

   if (__dpmi_get_segment_base_address(_my_cs(), &baseaddr) == -1)
      return (-1);

   region.handle = 0;
   region.size = size;
   region.address = baseaddr + (uint32_t)a;

   if (__dpmi_lock_linear_region(&region) == -1)
      return (-1);

   return 0;
}