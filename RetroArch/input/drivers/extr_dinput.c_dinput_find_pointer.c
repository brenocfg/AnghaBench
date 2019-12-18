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
struct pointer_status {int pointer_id; struct pointer_status* next; } ;
struct TYPE_2__ {struct pointer_status* next; } ;
struct dinput_input {TYPE_1__ pointer_head; } ;

/* Variables and functions */

__attribute__((used)) static struct pointer_status *dinput_find_pointer(
      struct dinput_input *di, int pointer_id)
{
   struct pointer_status *check_pos = di->pointer_head.next;

   while (check_pos)
   {
      if (check_pos->pointer_id == pointer_id)
         break;
      check_pos = check_pos->next;
   }

   return check_pos;
}