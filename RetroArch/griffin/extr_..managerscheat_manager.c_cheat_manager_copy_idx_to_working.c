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
struct TYPE_4__ {unsigned int size; char* working_desc; char* working_code; TYPE_1__* cheats; int /*<<< orphan*/  working_cheat; } ;
struct TYPE_3__ {scalar_t__ code; scalar_t__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_CODE_SCRATCH_SIZE ; 
 int /*<<< orphan*/  CHEAT_DESC_SCRATCH_SIZE ; 
 TYPE_2__ cheat_manager_state ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 

bool cheat_manager_copy_idx_to_working(unsigned idx)
{
   if ((!cheat_manager_state.cheats) || (cheat_manager_state.size < idx + 1))
      return false;

   memcpy(&(cheat_manager_state.working_cheat), &(cheat_manager_state.cheats[idx]), sizeof(struct item_cheat));

   if (cheat_manager_state.cheats[idx].desc)
      strlcpy(cheat_manager_state.working_desc, cheat_manager_state.cheats[idx].desc, CHEAT_DESC_SCRATCH_SIZE);
   else
      cheat_manager_state.working_desc[0] = '\0';

   if (cheat_manager_state.cheats[idx].code)
      strlcpy(cheat_manager_state.working_code, cheat_manager_state.cheats[idx].code, CHEAT_CODE_SCRATCH_SIZE);
   else
      cheat_manager_state.working_code[0] = '\0';

   return true;
}