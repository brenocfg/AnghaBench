#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int ptr; int /*<<< orphan*/  cheats; } ;

/* Variables and functions */
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  cheat_manager_update (TYPE_1__*,int) ; 

void cheat_manager_index_next(void)
{
   if (!cheat_manager_state.cheats || cheat_manager_state.size == 0)
      return;

   cheat_manager_state.ptr = (cheat_manager_state.ptr + 1) % cheat_manager_state.size;
   cheat_manager_update(&cheat_manager_state, cheat_manager_state.ptr);
}