#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ apply_cheats_after_load; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_IS_DATA_INITED ; 
 int /*<<< orphan*/ * bsv_movie_state_handle ; 
 int /*<<< orphan*/  cheat_manager_alloc_if_empty () ; 
 int /*<<< orphan*/  cheat_manager_apply_cheats () ; 
 int /*<<< orphan*/  cheat_manager_load_game_specific_cheats () ; 
 TYPE_2__* configuration_settings ; 
 int /*<<< orphan*/  netplay_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void command_event_init_cheats(void)
{
   settings_t *settings          = configuration_settings;
   bool        allow_cheats      = true;

#ifdef HAVE_NETWORKING
   allow_cheats &= !netplay_driver_ctl(
         RARCH_NETPLAY_CTL_IS_DATA_INITED, NULL);
#endif
   allow_cheats &= !(bsv_movie_state_handle != NULL);

   if (!allow_cheats)
      return;

   cheat_manager_alloc_if_empty();
   cheat_manager_load_game_specific_cheats();

   if (settings && settings->bools.apply_cheats_after_load)
      cheat_manager_apply_cheats();
}