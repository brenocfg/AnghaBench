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
struct rio_info {scalar_t__ RIOPrintDisabled; } ;
struct Host {TYPE_2__* Mapping; } ;
struct TYPE_4__ {int Flags; TYPE_1__* Topology; int /*<<< orphan*/  Name; } ;
struct TYPE_3__ {unsigned int Unit; int /*<<< orphan*/  Link; } ;

/* Variables and functions */
 int BEEN_HERE ; 
 scalar_t__ DO_PRINT ; 
 unsigned int LINKS_PER_UNIT ; 
 unsigned int MAX_RUP ; 
 int /*<<< orphan*/  NO_LINK ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 unsigned int ROUTE_DISCONNECT ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int RIOIsolate(struct rio_info *p, struct Host *HostP, unsigned int UnitId)
{
	unsigned int link, unit;

	UnitId--;		/* this trick relies on the Unit Id being UNSIGNED! */

	if (UnitId >= MAX_RUP)	/* dontcha just lurv unsigned maths! */
		return (0);

	if (HostP->Mapping[UnitId].Flags & BEEN_HERE)
		return (0);

	HostP->Mapping[UnitId].Flags |= BEEN_HERE;

	if (p->RIOPrintDisabled == DO_PRINT)
		rio_dprintk(RIO_DEBUG_ROUTE, "RIOMesgIsolated %s", HostP->Mapping[UnitId].Name);

	for (link = 0; link < LINKS_PER_UNIT; link++) {
		unit = HostP->Mapping[UnitId].Topology[link].Unit;
		HostP->Mapping[UnitId].Topology[link].Unit = ROUTE_DISCONNECT;
		HostP->Mapping[UnitId].Topology[link].Link = NO_LINK;
		RIOIsolate(p, HostP, unit);
	}
	HostP->Mapping[UnitId].Flags &= ~BEEN_HERE;
	return 1;
}