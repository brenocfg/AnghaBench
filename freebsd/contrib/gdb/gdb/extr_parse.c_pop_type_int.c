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
struct TYPE_2__ {int int_val; } ;

/* Variables and functions */
 TYPE_1__* type_stack ; 
 int type_stack_depth ; 

int
pop_type_int (void)
{
  if (type_stack_depth)
    return type_stack[--type_stack_depth].int_val;
  /* "Can't happen".  */
  return 0;
}