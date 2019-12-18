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
struct rio_info {unsigned int* RIOBindTab; } ;
struct Host {unsigned int UniqueNum; } ;

/* Variables and functions */
 int MAX_RTA_BINDINGS ; 

int RIOBootOk(struct rio_info *p, struct Host *HostP, unsigned long RtaUniq)
{
	int Entry;
	unsigned int HostUniq = HostP->UniqueNum;

	/*
	 ** Search bindings table for RTA or its parent.
	 ** If it exists, return 0, else 1.
	 */
	for (Entry = 0; (Entry < MAX_RTA_BINDINGS) && (p->RIOBindTab[Entry] != 0); Entry++) {
		if ((p->RIOBindTab[Entry] == HostUniq) || (p->RIOBindTab[Entry] == RtaUniq))
			return 0;
	}
	return 1;
}