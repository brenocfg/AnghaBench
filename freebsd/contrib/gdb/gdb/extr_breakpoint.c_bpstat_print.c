#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum print_stop_action { ____Placeholder_print_stop_action } print_stop_action ;
typedef  TYPE_1__* bpstat ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int PRINT_NOTHING ; 
 int PRINT_SRC_AND_LOC ; 
 int PRINT_SRC_ONLY ; 
 int PRINT_UNKNOWN ; 
 int print_bp_stop_message (TYPE_1__*) ; 

enum print_stop_action
bpstat_print (bpstat bs)
{
  int val;

  /* Maybe another breakpoint in the chain caused us to stop.
     (Currently all watchpoints go on the bpstat whether hit or not.
     That probably could (should) be changed, provided care is taken
     with respect to bpstat_explains_signal).  */
  for (; bs; bs = bs->next)
    {
      val = print_bp_stop_message (bs);
      if (val == PRINT_SRC_ONLY 
	  || val == PRINT_SRC_AND_LOC 
	  || val == PRINT_NOTHING)
	return val;
    }

  /* We reached the end of the chain, or we got a null BS to start
     with and nothing was printed. */
  return PRINT_UNKNOWN;
}