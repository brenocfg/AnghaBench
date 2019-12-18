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

/* Variables and functions */
 scalar_t__ ctr_get_stack_free () ; 

u32 ctr_get_stack_usage(void)
{
   extern u32 __stacksize__;
   u32 stack_free = ctr_get_stack_free();

   return __stacksize__ > stack_free? __stacksize__ - stack_free: 0;
}