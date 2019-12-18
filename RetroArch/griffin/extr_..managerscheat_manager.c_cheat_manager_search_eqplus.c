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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_SEARCH_TYPE_EQPLUS ; 
 int cheat_manager_search (int /*<<< orphan*/ ) ; 

int cheat_manager_search_eqplus(rarch_setting_t *setting, bool wraparound)
{
   return cheat_manager_search(CHEAT_SEARCH_TYPE_EQPLUS);
}