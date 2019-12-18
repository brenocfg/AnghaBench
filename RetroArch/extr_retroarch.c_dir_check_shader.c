#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rarch_dir_list {int ptr; TYPE_2__* list; } ;
struct TYPE_4__ {int size; TYPE_1__* elems; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  command_set_shader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_shader_list ; 

__attribute__((used)) static void dir_check_shader(bool pressed_next, bool pressed_prev)
{
   struct rarch_dir_list *dir_list = (struct rarch_dir_list*)&dir_shader_list;
   static bool change_triggered = false;

   if (!dir_list || !dir_list->list)
      return;

   if (pressed_next)
   {
      if (change_triggered)
         dir_list->ptr = (dir_list->ptr + 1) %
            dir_list->list->size;
   }
   else if (pressed_prev)
   {
      if (dir_list->ptr == 0)
         dir_list->ptr = dir_list->list->size - 1;
      else
         dir_list->ptr--;
   }
   else
      return;
   change_triggered = true;

   command_set_shader(dir_list->list->elems[dir_list->ptr].data);
}