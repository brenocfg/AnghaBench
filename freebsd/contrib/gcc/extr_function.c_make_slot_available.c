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
struct temp_slot {int level; scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  avail_temp_slots ; 
 int /*<<< orphan*/  cut_slot_from_list (struct temp_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_slot_to_list (struct temp_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_slots_at_level (int) ; 

__attribute__((used)) static void
make_slot_available (struct temp_slot *temp)
{
  cut_slot_from_list (temp, temp_slots_at_level (temp->level));
  insert_slot_to_list (temp, &avail_temp_slots);
  temp->in_use = 0;
  temp->level = -1;
}