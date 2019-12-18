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
struct pointer_status {struct pointer_status* next; } ;
struct dinput_input {struct pointer_status pointer_head; } ;

/* Variables and functions */

__attribute__((used)) static void dinput_add_pointer(struct dinput_input *di,
      struct pointer_status *new_pointer)
{
   struct pointer_status *insert_pos = NULL;

   new_pointer->next = NULL;
   insert_pos = &di->pointer_head;

   while (insert_pos->next)
      insert_pos = insert_pos->next;
   insert_pos->next = new_pointer;
}