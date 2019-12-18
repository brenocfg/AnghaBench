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
struct decision_head {struct decision* first; } ;
struct decision {scalar_t__ subroutine_number; struct decision_head success; struct decision* next; } ;

/* Variables and functions */
 int SUBROUTINE_THRESHOLD ; 
 scalar_t__ next_subroutine_number ; 

__attribute__((used)) static int
break_out_subroutines (struct decision_head *head, int initial)
{
  int size = 0;
  struct decision *sub;

  for (sub = head->first; sub; sub = sub->next)
    size += 1 + break_out_subroutines (&sub->success, 0);

  if (size > SUBROUTINE_THRESHOLD && ! initial)
    {
      head->first->subroutine_number = ++next_subroutine_number;
      size = 1;
    }
  return size;
}