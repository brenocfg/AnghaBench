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
struct call_struc {struct call_struc* next; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct call_struc* divert_head ; 
 int /*<<< orphan*/  divert_lock ; 
 int /*<<< orphan*/  kfree (struct call_struc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void deleteprocs(void)
{ struct call_struc *cs, *cs1; 
  unsigned long flags;

  spin_lock_irqsave(&divert_lock, flags);
  cs = divert_head;
  divert_head = NULL;
  while (cs)
   { del_timer(&cs->timer);
     cs1 = cs;
     cs = cs->next;
     kfree(cs1);
   } 
  spin_unlock_irqrestore(&divert_lock, flags);
}