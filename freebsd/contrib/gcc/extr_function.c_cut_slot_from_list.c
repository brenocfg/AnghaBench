#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct temp_slot {struct temp_slot* next; TYPE_1__* prev; } ;
struct TYPE_2__ {struct temp_slot* next; } ;

/* Variables and functions */

__attribute__((used)) static void
cut_slot_from_list (struct temp_slot *temp, struct temp_slot **list)
{
  if (temp->next)
    temp->next->prev = temp->prev;
  if (temp->prev)
    temp->prev->next = temp->next;
  else
    *list = temp->next;

  temp->prev = temp->next = NULL;
}