#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  cheat_file ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 scalar_t__ cheat_manager_get_game_specific_filename (char*,int,int) ; 
 int /*<<< orphan*/  cheat_manager_load (char*,int) ; 

void cheat_manager_load_game_specific_cheats(void)
{
   char cheat_file[PATH_MAX_LENGTH];

   if (cheat_manager_get_game_specific_filename(
            cheat_file, sizeof(cheat_file), false))
   {
      RARCH_LOG("[Cheats]: Load game-specific cheatfile: %s\n", cheat_file);
      cheat_manager_load(cheat_file, true);
   }
}