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
struct item_cheat {int dummy; } ;
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/  working_code; TYPE_1__* cheats; int /*<<< orphan*/  working_desc; int /*<<< orphan*/  working_cheat; } ;
struct TYPE_3__ {void* code; void* desc; } ;

/* Variables and functions */
 TYPE_2__ cheat_manager_state ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

bool cheat_manager_copy_working_to_idx(unsigned idx)
{
   if ((!cheat_manager_state.cheats) || (cheat_manager_state.size < idx + 1))
      return false;

   memcpy(&(cheat_manager_state.cheats[idx]), &(cheat_manager_state.working_cheat), sizeof(struct item_cheat));

   if (cheat_manager_state.cheats[idx].desc)
      free(cheat_manager_state.cheats[idx].desc);

   cheat_manager_state.cheats[idx].desc = strdup(cheat_manager_state.working_desc);

   if (cheat_manager_state.cheats[idx].code)
      free(cheat_manager_state.cheats[idx].code);

   cheat_manager_state.cheats[idx].code = strdup(cheat_manager_state.working_code);

   return true;
}