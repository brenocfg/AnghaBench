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
struct pointer_status {int pointer_id; struct pointer_status* next; } ;
struct dinput_input {struct pointer_status pointer_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pointer_status*) ; 

__attribute__((used)) static void dinput_delete_pointer(struct dinput_input *di, int pointer_id)
{
   struct pointer_status *check_pos = &di->pointer_head;

   while (check_pos && check_pos->next)
   {
      if (check_pos->next->pointer_id == pointer_id)
      {
         struct pointer_status *to_delete = check_pos->next;

         check_pos->next = check_pos->next->next;
         free(to_delete);
      }
      check_pos = check_pos->next;
   }
}