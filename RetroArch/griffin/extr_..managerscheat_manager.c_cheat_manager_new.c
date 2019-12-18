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
struct item_cheat {int state; int repeat_count; int repeat_add_to_address; scalar_t__ repeat_add_to_value; int /*<<< orphan*/ * code; int /*<<< orphan*/ * desc; } ;
struct TYPE_2__ {unsigned int buf_size; unsigned int size; int search_bit_size; struct item_cheat* cheats; } ;

/* Variables and functions */
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  cheat_manager_free () ; 
 TYPE_1__ cheat_manager_state ; 

__attribute__((used)) static void cheat_manager_new(unsigned size)
{
   unsigned i;

   cheat_manager_free();

   cheat_manager_state.buf_size        = size;
   cheat_manager_state.size            = size;
   cheat_manager_state.search_bit_size = 3;
   cheat_manager_state.cheats          = (struct item_cheat*)
         calloc(cheat_manager_state.buf_size, sizeof(struct item_cheat));

   if (!cheat_manager_state.cheats)
   {
      cheat_manager_state.buf_size    = 0;
      cheat_manager_state.size        = 0;
      cheat_manager_state.cheats      = NULL;
      return;
   }

   for (i = 0; i < cheat_manager_state.size; i++)
   {
      cheat_manager_state.cheats[i].desc                  = NULL;
      cheat_manager_state.cheats[i].code                  = NULL;
      cheat_manager_state.cheats[i].state                 = false;
      cheat_manager_state.cheats[i].repeat_count          = 1;
      cheat_manager_state.cheats[i].repeat_add_to_value   = 0;
      cheat_manager_state.cheats[i].repeat_add_to_address = 1;
   }
}