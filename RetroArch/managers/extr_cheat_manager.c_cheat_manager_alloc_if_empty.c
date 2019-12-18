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
struct TYPE_2__ {int /*<<< orphan*/  cheats; } ;

/* Variables and functions */
 int /*<<< orphan*/  cheat_manager_new (int /*<<< orphan*/ ) ; 
 TYPE_1__ cheat_manager_state ; 

bool cheat_manager_alloc_if_empty(void)
{
   if (!cheat_manager_state.cheats)
      cheat_manager_new(0);

   return true;
}