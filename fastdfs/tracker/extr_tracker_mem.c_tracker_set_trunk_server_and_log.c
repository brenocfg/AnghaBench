#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* last_trunk_server_id; TYPE_1__* pTrunkServer; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSStorageDetail ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int tracker_write_to_trunk_change_log (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int tracker_set_trunk_server_and_log(FDFSGroupInfo *pGroup, \
		FDFSStorageDetail *pNewTrunkServer)
{
	FDFSStorageDetail *pLastTrunkServer;

	pLastTrunkServer = pGroup->pTrunkServer;
	pGroup->pTrunkServer = pNewTrunkServer;
	if (pNewTrunkServer == NULL || strcmp(pNewTrunkServer->id, \
					pGroup->last_trunk_server_id) != 0)
	{
		int result;
		result = tracker_write_to_trunk_change_log(pGroup, \
				pLastTrunkServer);
		if (pNewTrunkServer == NULL)
		{
			*(pGroup->last_trunk_server_id) = '\0';
		}
		else
		{
			strcpy(pGroup->last_trunk_server_id, \
				pNewTrunkServer->id);
		}
		return result;
	}

	return 0;
}