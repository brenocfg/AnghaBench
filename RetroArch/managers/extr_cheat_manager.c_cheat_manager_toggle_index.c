#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ apply_cheats_after_toggle; } ;
struct TYPE_9__ {TYPE_2__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {scalar_t__ size; TYPE_1__* cheats; } ;
struct TYPE_7__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cheat_manager_apply_cheats () ; 
 TYPE_5__ cheat_manager_state ; 
 int /*<<< orphan*/  cheat_manager_update (TYPE_5__*,unsigned int) ; 
 TYPE_3__* config_get_ptr () ; 

void cheat_manager_toggle_index(unsigned i)
{
   settings_t *settings = config_get_ptr();
   if (!cheat_manager_state.cheats || cheat_manager_state.size == 0)
      return;

   cheat_manager_state.cheats[i].state = !cheat_manager_state.cheats[i].state;
   cheat_manager_update(&cheat_manager_state, i);

   if (!settings)
      return;

   if (settings->bools.apply_cheats_after_toggle)
      cheat_manager_apply_cheats();
}