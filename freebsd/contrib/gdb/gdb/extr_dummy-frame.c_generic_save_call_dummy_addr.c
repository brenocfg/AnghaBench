#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* call_hi; void* call_lo; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 TYPE_1__* dummy_frame_stack ; 

void
generic_save_call_dummy_addr (CORE_ADDR lo, CORE_ADDR hi)
{
  dummy_frame_stack->call_lo = lo;
  dummy_frame_stack->call_hi = hi;
}