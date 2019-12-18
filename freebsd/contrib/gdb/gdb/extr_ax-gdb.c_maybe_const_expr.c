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
typedef  union exp_element {int dummy; } exp_element ;
struct value {int dummy; } ;

/* Variables and functions */
 struct value* const_expr (union exp_element**) ; 

__attribute__((used)) static struct value *
maybe_const_expr (union exp_element **pc)
{
  union exp_element *tentative_pc = *pc;
  struct value *v = const_expr (&tentative_pc);

  /* If we got a value, then update the real PC.  */
  if (v)
    *pc = tentative_pc;

  return v;
}