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
struct TYPE_2__ {unsigned int loading_cheat_size; } ;

/* Variables and functions */
 TYPE_1__ cheat_manager_state ; 
 scalar_t__ errno ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cheat_manager_load_cb_first_pass(char *key, char *value)
{
   errno = 0;

   if (string_is_equal(key, "cheats"))
   {
      cheat_manager_state.loading_cheat_size = (unsigned)strtoul(value, NULL, 0);

      if (errno != 0)
         cheat_manager_state.loading_cheat_size = 0;
   }
}