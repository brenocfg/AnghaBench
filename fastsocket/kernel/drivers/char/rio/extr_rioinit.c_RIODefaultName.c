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
struct rio_info {struct Host* RIOHosts; } ;
struct Host {TYPE_1__* Mapping; } ;
struct TYPE_2__ {int* Name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

int RIODefaultName(struct rio_info *p, struct Host *HostP, unsigned int	UnitId)
{
	memcpy(HostP->Mapping[UnitId].Name, "UNKNOWN RTA X-XX", 17);
	HostP->Mapping[UnitId].Name[12]='1'+(HostP-p->RIOHosts);
	if ((UnitId+1) > 9) {
		HostP->Mapping[UnitId].Name[14]='0'+((UnitId+1)/10);
		HostP->Mapping[UnitId].Name[15]='0'+((UnitId+1)%10);
	}
	else {
		HostP->Mapping[UnitId].Name[14]='1'+UnitId;
		HostP->Mapping[UnitId].Name[15]=0;
	}
	return 0;
}