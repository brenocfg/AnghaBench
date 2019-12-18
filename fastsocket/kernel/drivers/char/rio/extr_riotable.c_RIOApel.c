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
struct rio_info {struct Map* RIOConnectTable; struct Host* RIOHosts; } ;
struct Map {int Flags; int /*<<< orphan*/  Name; int /*<<< orphan*/ * Topology; int /*<<< orphan*/  SysPort; scalar_t__ ID; scalar_t__ RtaUniqueNum; int /*<<< orphan*/  HostUniqueNum; } ;
struct Host {int Flags; int /*<<< orphan*/  HostLock; struct Map* Mapping; int /*<<< orphan*/  Name; int /*<<< orphan*/ * Topology; int /*<<< orphan*/  UniqueNum; } ;

/* Variables and functions */
 int LINKS_PER_UNIT ; 
 int /*<<< orphan*/  MAX_NAME_LEN ; 
 int MAX_RUP ; 
 int /*<<< orphan*/  NO_PORT ; 
 int RC_RUNNING ; 
 int /*<<< orphan*/  RIO_DEBUG_TABLE ; 
 int RIO_HOSTS ; 
 int RTA16_SECOND_SLOT ; 
 int RUN_STATE ; 
 int SLOT_IN_USE ; 
 int SLOT_TENTATIVE ; 
 int TOTAL_MAP_ENTRIES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct Map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int RIOApel(struct rio_info *p)
{
	int Host;
	int link;
	int Rup;
	int Next = 0;
	struct Map *MapP;
	struct Host *HostP;
	unsigned long flags;

	rio_dprintk(RIO_DEBUG_TABLE, "Generating a table to return to config.rio\n");

	memset(&p->RIOConnectTable[0], 0, sizeof(struct Map) * TOTAL_MAP_ENTRIES);

	for (Host = 0; Host < RIO_HOSTS; Host++) {
		rio_dprintk(RIO_DEBUG_TABLE, "Processing host %d\n", Host);
		HostP = &p->RIOHosts[Host];
		rio_spin_lock_irqsave(&HostP->HostLock, flags);

		MapP = &p->RIOConnectTable[Next++];
		MapP->HostUniqueNum = HostP->UniqueNum;
		if ((HostP->Flags & RUN_STATE) != RC_RUNNING) {
			rio_spin_unlock_irqrestore(&HostP->HostLock, flags);
			continue;
		}
		MapP->RtaUniqueNum = 0;
		MapP->ID = 0;
		MapP->Flags = SLOT_IN_USE;
		MapP->SysPort = NO_PORT;
		for (link = 0; link < LINKS_PER_UNIT; link++)
			MapP->Topology[link] = HostP->Topology[link];
		memcpy(MapP->Name, HostP->Name, MAX_NAME_LEN);
		for (Rup = 0; Rup < MAX_RUP; Rup++) {
			if (HostP->Mapping[Rup].Flags & (SLOT_IN_USE | SLOT_TENTATIVE)) {
				p->RIOConnectTable[Next] = HostP->Mapping[Rup];
				if (HostP->Mapping[Rup].Flags & SLOT_IN_USE)
					p->RIOConnectTable[Next].Flags |= SLOT_IN_USE;
				if (HostP->Mapping[Rup].Flags & SLOT_TENTATIVE)
					p->RIOConnectTable[Next].Flags |= SLOT_TENTATIVE;
				if (HostP->Mapping[Rup].Flags & RTA16_SECOND_SLOT)
					p->RIOConnectTable[Next].Flags |= RTA16_SECOND_SLOT;
				Next++;
			}
		}
		rio_spin_unlock_irqrestore(&HostP->HostLock, flags);
	}
	return 0;
}