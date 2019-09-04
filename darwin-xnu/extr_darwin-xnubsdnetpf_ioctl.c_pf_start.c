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
struct TYPE_2__ {int running; int stateid; int /*<<< orphan*/  since; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  pf_calendar_time_second () ; 
 int pf_is_enabled ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pf_purge_thread_fn ; 
 TYPE_1__ pf_status ; 
 int pf_time_second () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_start(void)
{
	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	VERIFY(pf_is_enabled == 0);

	pf_is_enabled = 1;
	pf_status.running = 1;
	pf_status.since = pf_calendar_time_second();
	if (pf_status.stateid == 0) {
		pf_status.stateid = pf_time_second();
		pf_status.stateid = pf_status.stateid << 32;
	}
	wakeup(pf_purge_thread_fn);
	DPFPRINTF(PF_DEBUG_MISC, ("pf: started\n"));
}