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
struct ifnet {int /*<<< orphan*/  if_flt_lock; int /*<<< orphan*/  if_flt_head; int /*<<< orphan*/  if_flt_waiters; scalar_t__ if_flt_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  if_flt_monitor_busy (struct ifnet*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
if_flt_monitor_enter(struct ifnet *ifp)
{
	LCK_MTX_ASSERT(&ifp->if_flt_lock, LCK_MTX_ASSERT_OWNED);

	while (ifp->if_flt_busy) {
		++ifp->if_flt_waiters;
		(void) msleep(&ifp->if_flt_head, &ifp->if_flt_lock,
		    (PZERO - 1), "if_flt_monitor", NULL);
	}
	if_flt_monitor_busy(ifp);
}