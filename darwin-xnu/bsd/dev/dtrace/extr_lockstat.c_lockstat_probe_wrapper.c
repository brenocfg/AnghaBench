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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  lockstat_probe (scalar_t__,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* lockstat_probemap ; 
 int /*<<< orphan*/  stub1 (scalar_t__,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lockstat_probe_wrapper(int probe, uintptr_t lp, int rwflag)
{
	dtrace_id_t id;
	id = lockstat_probemap[probe];
	if (id != 0)
	{
		(*lockstat_probe)(id, (uintptr_t)lp, (uint64_t)rwflag, 0,0,0);
	}
}