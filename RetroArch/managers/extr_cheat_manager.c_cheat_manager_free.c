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
struct TYPE_4__ {unsigned int size; int memory_initialized; int memory_search_initialized; scalar_t__ total_memory_size; scalar_t__ num_memory_buffers; TYPE_1__* matches; TYPE_1__* memory_size_list; TYPE_1__* memory_buf_list; int /*<<< orphan*/ * curr_memory_buf; TYPE_1__* prev_memory_buf; scalar_t__ buf_size; TYPE_1__* cheats; } ;
struct TYPE_3__ {struct TYPE_3__* code; struct TYPE_3__* desc; } ;

/* Variables and functions */
 TYPE_2__ cheat_manager_state ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void cheat_manager_free(void)
{
   unsigned i = 0;

   if (cheat_manager_state.cheats)
   {
      for (i = 0; i < cheat_manager_state.size; i++)
      {
         if (cheat_manager_state.cheats[i].desc)
            free(cheat_manager_state.cheats[i].desc);
         if (cheat_manager_state.cheats[i].code)
            free(cheat_manager_state.cheats[i].code);
      }

      free(cheat_manager_state.cheats);
   }

   if (cheat_manager_state.prev_memory_buf)
      free(cheat_manager_state.prev_memory_buf);

   if (cheat_manager_state.matches)
      free(cheat_manager_state.matches);

   if (cheat_manager_state.memory_buf_list)
      free(cheat_manager_state.memory_buf_list);

   if (cheat_manager_state.memory_size_list)
      free(cheat_manager_state.memory_size_list);

   cheat_manager_state.cheats = NULL;
   cheat_manager_state.size = 0;
   cheat_manager_state.buf_size = 0;
   cheat_manager_state.prev_memory_buf = NULL;
   cheat_manager_state.curr_memory_buf = NULL;
   cheat_manager_state.memory_buf_list = NULL;
   cheat_manager_state.memory_size_list = NULL;
   cheat_manager_state.matches = NULL;
   cheat_manager_state.num_memory_buffers = 0;
   cheat_manager_state.total_memory_size = 0;
   cheat_manager_state.memory_initialized = false;
   cheat_manager_state.memory_search_initialized = false;

}