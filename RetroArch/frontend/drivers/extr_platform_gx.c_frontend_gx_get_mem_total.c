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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSMEM1_SIZE ; 
 scalar_t__ gx_mem2_total () ; 

__attribute__((used)) static uint64_t frontend_gx_get_mem_total(void)
{
   uint64_t total = SYSMEM1_SIZE;
#if defined(HW_RVL) && !defined(IS_SALAMANDER)
   total += gx_mem2_total();
#endif
   return total;
}