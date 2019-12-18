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
struct TYPE_4__ {int /*<<< orphan*/  Error; } ;
struct rio_info {int RIONumHosts; TYPE_2__ RIOError; TYPE_1__* RIOHosts; } ;
struct Map {scalar_t__ HostUniqueNum; scalar_t__ RtaUniqueNum; int ID; char* Name; scalar_t__ SysPort; } ;
struct TYPE_3__ {scalar_t__ UniqueNum; int Flags; char* Name; struct Map* Mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CHARACTER_IN_NAME ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  HOST_NOT_RUNNING ; 
 int /*<<< orphan*/  ID_NUMBER_OUT_OF_RANGE ; 
 int MAX_NAME_LEN ; 
 int MAX_RUP ; 
 int RC_RUNNING ; 
 int /*<<< orphan*/  RIO_DEBUG_TABLE ; 
 int /*<<< orphan*/  RTA_NUMBER_WRONG ; 
 int RUN_STATE ; 
 int /*<<< orphan*/  UNKNOWN_HOST_NUMBER ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 

int RIOChangeName(struct rio_info *p, struct Map *MapP)
{
	int host;
	struct Map *HostMapP;
	char *sptr;

	rio_dprintk(RIO_DEBUG_TABLE, "Change name entry on host %x, rta %x, ID %d, Sysport %d\n", MapP->HostUniqueNum, MapP->RtaUniqueNum, MapP->ID, (int) MapP->SysPort);

	if (MapP->ID > MAX_RUP) {
		rio_dprintk(RIO_DEBUG_TABLE, "Bad ID in map entry!\n");
		p->RIOError.Error = ID_NUMBER_OUT_OF_RANGE;
		return -EINVAL;
	}

	MapP->Name[MAX_NAME_LEN - 1] = '\0';
	sptr = MapP->Name;

	while (*sptr) {
		if (*sptr < ' ' || *sptr > '~') {
			rio_dprintk(RIO_DEBUG_TABLE, "Name entry contains non-printing characters!\n");
			p->RIOError.Error = BAD_CHARACTER_IN_NAME;
			return -EINVAL;
		}
		sptr++;
	}

	for (host = 0; host < p->RIONumHosts; host++) {
		if (MapP->HostUniqueNum == p->RIOHosts[host].UniqueNum) {
			if ((p->RIOHosts[host].Flags & RUN_STATE) != RC_RUNNING) {
				p->RIOError.Error = HOST_NOT_RUNNING;
				return -ENXIO;
			}
			if (MapP->ID == 0) {
				memcpy(p->RIOHosts[host].Name, MapP->Name, MAX_NAME_LEN);
				return 0;
			}

			HostMapP = &p->RIOHosts[host].Mapping[MapP->ID - 1];

			if (HostMapP->RtaUniqueNum != MapP->RtaUniqueNum) {
				p->RIOError.Error = RTA_NUMBER_WRONG;
				return -ENXIO;
			}
			memcpy(HostMapP->Name, MapP->Name, MAX_NAME_LEN);
			return 0;
		}
	}
	p->RIOError.Error = UNKNOWN_HOST_NUMBER;
	rio_dprintk(RIO_DEBUG_TABLE, "Unknown host %x\n", MapP->HostUniqueNum);
	return -ENXIO;
}