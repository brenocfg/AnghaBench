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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  lwp_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fasttrap_anarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ttolwp (int /*<<< orphan*/ ) ; 

uint64_t
fasttrap_usdt_getarg(void *arg, dtrace_id_t id, void *parg, int argno, int aframes)
{
#pragma unused(arg, id, parg, argno, aframes)
#if 0
	return (fasttrap_anarg(ttolwp(curthread)->lwp_regs, 0, argno));
#endif

	return 0;
}