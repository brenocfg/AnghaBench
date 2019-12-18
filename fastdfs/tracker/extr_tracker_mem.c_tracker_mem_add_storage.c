#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pStorage; int /*<<< orphan*/  pGroup; } ;
typedef  TYPE_1__ TrackerClientInfo ;
typedef  int /*<<< orphan*/  FDFSStorageDetail ;

/* Variables and functions */
 int _tracker_mem_add_storage (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*,char const*,int const,int const,int*) ; 

__attribute__((used)) static int tracker_mem_add_storage(TrackerClientInfo *pClientInfo,
		const char *id, const char *ip_addr,
		const bool bNeedSleep, const bool bNeedLock, bool *bInserted)
{
	int result;
	FDFSStorageDetail *pStorageServer;

	pStorageServer = NULL;
	result = _tracker_mem_add_storage(pClientInfo->pGroup, \
			&pStorageServer, id, ip_addr, bNeedSleep, \
			bNeedLock, bInserted);
	if (result == 0)
	{
		pClientInfo->pStorage = pStorageServer;
	}

	return result;
}