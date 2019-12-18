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
struct item_cheat {int state; unsigned int handler; int memory_search_size; unsigned int idx; int repeat_count; int repeat_add_to_address; scalar_t__ repeat_add_to_value; int /*<<< orphan*/  cheat_type; scalar_t__ desc; scalar_t__ code; } ;
struct TYPE_2__ {unsigned int size; unsigned int buf_size; struct item_cheat* cheats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_TYPE_SET_TO_VALUE ; 
 scalar_t__ calloc (unsigned int,int) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct item_cheat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (struct item_cheat*,unsigned int) ; 

bool cheat_manager_realloc(unsigned new_size, unsigned default_handler)
{
   unsigned i;
   unsigned orig_size = 0;

   if (!cheat_manager_state.cheats)
   {
      cheat_manager_state.cheats = (struct item_cheat*)
            calloc(new_size, sizeof(struct item_cheat));
      orig_size = 0;
   }
   else
   {
      struct item_cheat *val = NULL;
      orig_size = cheat_manager_state.size;

      /* if size is decreasing, free the items that will be lost */
      for (i = new_size; i < orig_size; i++)
      {
         if (cheat_manager_state.cheats[i].code)
            free(cheat_manager_state.cheats[i].code);
         if (cheat_manager_state.cheats[i].desc)
            free(cheat_manager_state.cheats[i].desc);
      }

      val = (struct item_cheat*)
            realloc(cheat_manager_state.cheats,
            new_size * sizeof(struct item_cheat));

      cheat_manager_state.cheats = val ? val : NULL;
   }

   if (!cheat_manager_state.cheats)
   {
      cheat_manager_state.buf_size = cheat_manager_state.size = 0;
      cheat_manager_state.cheats = NULL;
      return false;
   }

   cheat_manager_state.buf_size = new_size;
   cheat_manager_state.size = new_size;

   for (i = orig_size; i < cheat_manager_state.size; i++)
   {
      memset(&(cheat_manager_state.cheats[i]), 0, sizeof(cheat_manager_state.cheats[i]));
      cheat_manager_state.cheats[i].state = false;
      cheat_manager_state.cheats[i].handler = default_handler;
      cheat_manager_state.cheats[i].cheat_type = CHEAT_TYPE_SET_TO_VALUE;
      cheat_manager_state.cheats[i].memory_search_size = 3;
      cheat_manager_state.cheats[i].idx = i;
      cheat_manager_state.cheats[i].repeat_count = 1;
      cheat_manager_state.cheats[i].repeat_add_to_value = 0;
      cheat_manager_state.cheats[i].repeat_add_to_address = 1;
   }

   return true;
}