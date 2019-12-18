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
struct temp_slot {struct temp_slot* prev; struct temp_slot* next; } ;

/* Variables and functions */

__attribute__((used)) static void
insert_slot_to_list (struct temp_slot *temp, struct temp_slot **list)
{
  temp->next = *list;
  if (*list)
    (*list)->prev = temp;
  temp->prev = NULL;
  *list = temp;
}