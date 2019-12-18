#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct string_list {int size; TYPE_1__* elems; } ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {TYPE_2__ target; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; TYPE_3__ value; } ;
typedef  TYPE_4__ rarch_setting_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct string_list* midi_driver_get_avail_inputs () ; 
 int string_list_find_elem (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setting_string_action_right_midi_input(rarch_setting_t *setting, bool wraparound)
{
   struct string_list *list = midi_driver_get_avail_inputs();

   if (list && list->size > 1)
   {
      int i = string_list_find_elem(list, setting->value.target.string);

      if (wraparound && i == (int)list->size)
         i = 0;
      if (i >= 0 && i < (int)list->size)
      {
         strlcpy(setting->value.target.string,
               list->elems[i].data, setting->size);
         return 0;
      }
   }

   return -1;
}