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
struct Host {TYPE_2__* Mapping; } ;
struct TYPE_4__ {int Flags; TYPE_1__* Topology; } ;
struct TYPE_3__ {unsigned int Unit; } ;

/* Variables and functions */
 int BEEN_HERE ; 
 unsigned int HOST_ID ; 
 unsigned char LINKS_PER_UNIT ; 
 unsigned int MAX_RUP ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int RIOCheck(struct Host *HostP, unsigned int UnitId)
{
	unsigned char link;

/* 	rio_dprint(RIO_DEBUG_ROUTE, ("Check to see if unit %d has a route to the host\n",UnitId)); */
	rio_dprintk(RIO_DEBUG_ROUTE, "RIOCheck : UnitID = %d\n", UnitId);

	if (UnitId == HOST_ID) {
		/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d is NOT isolated - it IS the host!\n", UnitId)); */
		return 1;
	}

	UnitId--;

	if (UnitId >= MAX_RUP) {
		/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d - ignored.\n", UnitId)); */
		return 0;
	}

	for (link = 0; link < LINKS_PER_UNIT; link++) {
		if (HostP->Mapping[UnitId].Topology[link].Unit == HOST_ID) {
			/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d is connected directly to host via link (%c).\n", 
			   UnitId, 'A'+link)); */
			return 1;
		}
	}

	if (HostP->Mapping[UnitId].Flags & BEEN_HERE) {
		/* rio_dprint(RIO_DEBUG_ROUTE, ("Been to Unit %d before - ignoring\n", UnitId)); */
		return 0;
	}

	HostP->Mapping[UnitId].Flags |= BEEN_HERE;

	for (link = 0; link < LINKS_PER_UNIT; link++) {
		/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d check link (%c)\n", UnitId,'A'+link)); */
		if (RIOCheck(HostP, HostP->Mapping[UnitId].Topology[link].Unit)) {
			/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d is connected to something that knows the host via link (%c)\n", UnitId,link+'A')); */
			HostP->Mapping[UnitId].Flags &= ~BEEN_HERE;
			return 1;
		}
	}

	HostP->Mapping[UnitId].Flags &= ~BEEN_HERE;

	/* rio_dprint(RIO_DEBUG_ROUTE, ("Unit %d DOESNT KNOW THE HOST!\n", UnitId)); */

	return 0;
}