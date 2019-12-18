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
struct temp_slot {struct temp_slot* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  combine_temp_slots () ; 
 int /*<<< orphan*/  make_slot_available (struct temp_slot*) ; 
 int /*<<< orphan*/  temp_slot_level ; 
 struct temp_slot** temp_slots_at_level (int /*<<< orphan*/ ) ; 

void
pop_temp_slots (void)
{
  struct temp_slot *p, *next;

  for (p = *temp_slots_at_level (temp_slot_level); p; p = next)
    {
      next = p->next;
      make_slot_available (p);
    }

  combine_temp_slots ();

  temp_slot_level--;
}