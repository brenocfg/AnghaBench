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
struct dummy_frame {scalar_t__ call_lo; scalar_t__ call_hi; struct dummy_frame* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DECR_PC_AFTER_BREAK ; 
 struct dummy_frame* dummy_frame_stack ; 

int
pc_in_dummy_frame (CORE_ADDR pc)
{
  struct dummy_frame *dummyframe;
  for (dummyframe = dummy_frame_stack;
       dummyframe != NULL;
       dummyframe = dummyframe->next)
    {
      if ((pc >= dummyframe->call_lo)
	  && (pc < dummyframe->call_hi + DECR_PC_AFTER_BREAK))
	return 1;
    }
  return 0;
}