#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
struct rio_info {int dummy; } ;
struct Map {int dummy; } ;
struct Host {TYPE_2__* Mapping; } ;
struct TYPE_5__ {int ID2; TYPE_1__* Topology; } ;
struct TYPE_4__ {scalar_t__ Unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBOLT ; 
 int LINKS_PER_UNIT ; 
 int /*<<< orphan*/  RIORemoveFromSavedTable (struct rio_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 scalar_t__ ROUTE_DISCONNECT ; 
 scalar_t__* TentTime ; 
 scalar_t__ WAIT_TO_FINISH ; 
 scalar_t__ current_time ; 
 scalar_t__ drv_getparm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ drv_hztousec (scalar_t__) ; 
 scalar_t__ elapse_time ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int RIOFreeDisconnected(struct rio_info *p, struct Host *HostP, int unit)
{
	int link;


	rio_dprintk(RIO_DEBUG_ROUTE, "RIOFreeDisconnect unit %d\n", unit);
	/*
	 ** If the slot is tentative and does not belong to the
	 ** second half of a 16 port RTA then scan to see if
	 ** is disconnected.
	 */
	for (link = 0; link < LINKS_PER_UNIT; link++) {
		if (HostP->Mapping[unit].Topology[link].Unit != ROUTE_DISCONNECT)
			break;
	}

	/*
	 ** If not all links are disconnected then we can forget about it.
	 */
	if (link < LINKS_PER_UNIT)
		return 1;

#ifdef NEED_TO_FIX_THIS
	/* Ok so all the links are disconnected. But we may have only just
	 ** made this slot tentative and not yet received a topology update.
	 ** Lets check how long ago we made it tentative.
	 */
	rio_dprintk(RIO_DEBUG_ROUTE, "Just about to check LBOLT on entry %d\n", unit);
	if (drv_getparm(LBOLT, (ulong_t *) & current_time))
		rio_dprintk(RIO_DEBUG_ROUTE, "drv_getparm(LBOLT,....) Failed.\n");

	elapse_time = current_time - TentTime[unit];
	rio_dprintk(RIO_DEBUG_ROUTE, "elapse %d = current %d - tent %d (%d usec)\n", elapse_time, current_time, TentTime[unit], drv_hztousec(elapse_time));
	if (drv_hztousec(elapse_time) < WAIT_TO_FINISH) {
		rio_dprintk(RIO_DEBUG_ROUTE, "Skipping slot %d, not timed out yet %d\n", unit, drv_hztousec(elapse_time));
		return 1;
	}
#endif

	/*
	 ** We have found an usable slot.
	 ** If it is half of a 16 port RTA then delete the other half.
	 */
	if (HostP->Mapping[unit].ID2 != 0) {
		int nOther = (HostP->Mapping[unit].ID2) - 1;

		rio_dprintk(RIO_DEBUG_ROUTE, "RioFreedis second slot %d.\n", nOther);
		memset(&HostP->Mapping[nOther], 0, sizeof(struct Map));
	}
	RIORemoveFromSavedTable(p, &HostP->Mapping[unit]);

	return 0;
}