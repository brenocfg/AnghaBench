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
typedef  int /*<<< orphan*/  target_storage ;
struct TYPE_8__ {int /*<<< orphan*/  active_count; int /*<<< orphan*/  active_servers; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSStorageDetail ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ bsearch (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_mem_cmp_by_storage_id ; 

__attribute__((used)) static FDFSStorageDetail *tracker_mem_get_active_storage_by_id( \
		FDFSGroupInfo *pGroup, const char *id)
{
	FDFSStorageDetail target_storage;
	FDFSStorageDetail *pTargetStorage;
	FDFSStorageDetail **ppStorageServer;

	if (id == NULL)
	{
		return NULL;
	}

	memset(&target_storage, 0, sizeof(target_storage));
	strcpy(target_storage.id, id);
	pTargetStorage = &target_storage;
	ppStorageServer = (FDFSStorageDetail **)bsearch(&pTargetStorage, \
			pGroup->active_servers, \
			pGroup->active_count, \
			sizeof(FDFSStorageDetail *), \
			tracker_mem_cmp_by_storage_id);
	if (ppStorageServer != NULL)
	{
		return *ppStorageServer;
	}
	else
	{
		return NULL;
	}
}