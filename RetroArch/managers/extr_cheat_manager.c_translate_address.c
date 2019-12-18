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
struct TYPE_2__ {unsigned int num_memory_buffers; unsigned int* memory_size_list; unsigned char** memory_buf_list; } ;

/* Variables and functions */
 TYPE_1__ cheat_manager_state ; 

__attribute__((used)) static unsigned translate_address(unsigned address, unsigned char **curr)
{
   unsigned offset = 0;
   unsigned i = 0;

   for (i = 0; i < cheat_manager_state.num_memory_buffers; i++)
   {
      if ((address >= offset) && (address < offset + cheat_manager_state.memory_size_list[i]))
      {
         *curr = cheat_manager_state.memory_buf_list[i];
         break;
      }
      else
         offset += cheat_manager_state.memory_size_list[i];
   }

   return offset;
}