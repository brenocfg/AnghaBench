#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_expr_p ;
struct TYPE_5__ {int value; struct TYPE_5__* next; } ;

/* Variables and functions */

__attribute__((used)) static inline value_expr_p
find_value_in_list (value_expr_p list, int value, value_expr_p *last_ptr)
{
  value_expr_p curr;
  value_expr_p last = NULL;

  for (curr = list; curr; last = curr, curr = curr->next)
    {
      if (curr->value == value)
        break;
    }
  if (last_ptr)
    *last_ptr = last;
  return curr;
}