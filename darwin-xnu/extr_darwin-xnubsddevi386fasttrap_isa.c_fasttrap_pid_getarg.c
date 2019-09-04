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
typedef  int /*<<< orphan*/  x86_saved_state_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fasttrap_anarg (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
fasttrap_pid_getarg(void *arg, dtrace_id_t id, void *parg, int argno,
    int aframes)
{
	pal_register_cache_state(current_thread(), VALID);
#pragma unused(arg, id, parg, aframes)
	return (fasttrap_anarg((x86_saved_state_t *)find_user_regs(current_thread()), 1, argno));
}