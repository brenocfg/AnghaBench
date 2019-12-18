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
struct rio_info {TYPE_1__* RIOSavedTable; } ;
struct Map {scalar_t__ RtaUniqueNum; } ;
struct TYPE_2__ {scalar_t__ RtaUniqueNum; } ;

/* Variables and functions */
 int TOTAL_MAP_ENTRIES ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int RIORemoveFromSavedTable(struct rio_info *p, struct Map *pMap)
{
	int entry;

	/*
	 ** We loop for all entries even after finding an entry and
	 ** zeroing it because we may have two entries to delete if
	 ** it's a 16 port RTA.
	 */
	for (entry = 0; entry < TOTAL_MAP_ENTRIES; entry++) {
		if (p->RIOSavedTable[entry].RtaUniqueNum == pMap->RtaUniqueNum) {
			memset(&p->RIOSavedTable[entry], 0, sizeof(struct Map));
		}
	}
	return 0;
}