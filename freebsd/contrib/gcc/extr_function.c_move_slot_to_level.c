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
struct temp_slot {int level; } ;

/* Variables and functions */
 int /*<<< orphan*/  cut_slot_from_list (struct temp_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_slot_to_list (struct temp_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_slots_at_level (int) ; 

__attribute__((used)) static void
move_slot_to_level (struct temp_slot *temp, int level)
{
  cut_slot_from_list (temp, temp_slots_at_level (temp->level));
  insert_slot_to_list (temp, temp_slots_at_level (level));
  temp->level = level;
}