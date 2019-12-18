#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__ const* pTrunkServer; } ;
struct TYPE_10__ {scalar_t__ status; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ const FDFSStorageDetail ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */
 int EALREADY ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENONET ; 
 int EOPNOTSUPP ; 
 scalar_t__ FDFS_STORAGE_STATUS_ACTIVE ; 
 scalar_t__ g_if_leader_self ; 
 scalar_t__ g_if_use_trunk_file ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int tracker_mem_do_set_trunk_server (TYPE_2__*,TYPE_1__ const*,int) ; 
 int tracker_mem_find_trunk_server (TYPE_2__*,int) ; 
 TYPE_1__ const* tracker_mem_get_storage (TYPE_2__*,char const*) ; 

const FDFSStorageDetail *tracker_mem_set_trunk_server( \
	FDFSGroupInfo *pGroup, const char *pStroageId, int *result)
{
	FDFSStorageDetail *pServer;
	FDFSStorageDetail *pTrunkServer;

	if (!(g_if_leader_self && g_if_use_trunk_file))
	{
		*result = EOPNOTSUPP;
		return NULL;
	}

	pTrunkServer = pGroup->pTrunkServer;
	if (pStroageId == NULL || *pStroageId == '\0')
	{
		if (pTrunkServer != NULL && pTrunkServer-> \
			status == FDFS_STORAGE_STATUS_ACTIVE)
		{
			*result = 0;
			return pTrunkServer;
		}

		*result = tracker_mem_find_trunk_server(pGroup, true);
		if (*result != 0)
		{
			return NULL;
		}
		return pGroup->pTrunkServer;
	}

	if (pTrunkServer != NULL && pTrunkServer->status == \
			FDFS_STORAGE_STATUS_ACTIVE)
	{
		if (strcmp(pStroageId, pTrunkServer->id) == 0)
		{
			*result = EALREADY;
		}
		else
		{
			*result = EEXIST;
		}
		return pTrunkServer;
	}

	pServer = tracker_mem_get_storage(pGroup, pStroageId);
	if (pServer == NULL)
	{
		*result = ENOENT;
		return NULL;
	}

	if (pServer->status != FDFS_STORAGE_STATUS_ACTIVE)
	{
		*result = ENONET;
		return NULL;
	}

	*result = tracker_mem_do_set_trunk_server(pGroup, \
			pServer, true);
	return *result == 0 ? pGroup->pTrunkServer : NULL;
}