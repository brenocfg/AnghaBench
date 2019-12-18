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
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_2__ {int /*<<< orphan*/  match_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_MATCH_ACTION_TYPE_COPY ; 
 int /*<<< orphan*/  cheat_manager_match_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ cheat_manager_state ; 

int cheat_manager_copy_match(rarch_setting_t *setting, bool wraparound)
{
   cheat_manager_match_action(CHEAT_MATCH_ACTION_TYPE_COPY,
         cheat_manager_state.match_idx, NULL, NULL, NULL, NULL);
   return 0;
}