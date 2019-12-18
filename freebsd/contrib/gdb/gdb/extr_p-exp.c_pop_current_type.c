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
struct type_push {struct type_push* next; int /*<<< orphan*/  stored; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_type ; 
 struct type_push* tp_top ; 
 int /*<<< orphan*/  xfree (struct type_push*) ; 

__attribute__((used)) static void
pop_current_type (void)
{
  struct type_push *tp = tp_top;
  if (tp)
    {
      current_type = tp->stored;
      tp_top = tp->next;
      xfree (tp);
    }
}