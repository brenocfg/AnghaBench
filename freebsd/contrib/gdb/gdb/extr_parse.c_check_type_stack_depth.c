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
typedef  union type_stack_elt {int dummy; } type_stack_elt ;

/* Variables and functions */
 union type_stack_elt* type_stack ; 
 int type_stack_depth ; 
 int type_stack_size ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static void
check_type_stack_depth (void)
{
  if (type_stack_depth == type_stack_size)
    {
      type_stack_size *= 2;
      type_stack = (union type_stack_elt *)
	xrealloc ((char *) type_stack, type_stack_size * sizeof (*type_stack));
    }
}