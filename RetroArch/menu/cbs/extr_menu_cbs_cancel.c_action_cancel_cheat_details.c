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
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {TYPE_1__ working_cheat; } ;

/* Variables and functions */
 int action_cancel_pop_default (char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  cheat_manager_copy_working_to_idx (int /*<<< orphan*/ ) ; 
 TYPE_2__ cheat_manager_state ; 

__attribute__((used)) static int action_cancel_cheat_details(const char *path,
      const char *label, unsigned type, size_t idx)
{
   cheat_manager_copy_working_to_idx(cheat_manager_state.working_cheat.idx) ;
   return action_cancel_pop_default(path, label, type, idx) ;
}