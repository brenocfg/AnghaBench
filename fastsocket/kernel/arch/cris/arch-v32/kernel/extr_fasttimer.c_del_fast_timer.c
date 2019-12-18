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
struct fast_timer {int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int detach_fast_timer (struct fast_timer*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

int del_fast_timer(struct fast_timer * t)
{
  unsigned long flags;
  int ret;

  local_irq_save(flags);
  ret = detach_fast_timer(t);
  t->next = t->prev = NULL;
  local_irq_restore(flags);
  return ret;
}